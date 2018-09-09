/*
**
** Copyright 2012, Samsung Electronics Co. LTD
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#ifndef EXYNOS_CAMERA_HW_IMPLEMENTATION_H
#define EXYNOS_CAMERA_HW_IMPLEMENTATION_H

#define START_HW_THREAD_ENABLE

#include <utils/threads.h>
#include <utils/RefBase.h>
#include <binder/MemoryBase.h>
#include <binder/MemoryHeapBase.h>
#include <hardware/camera.h>
#include <hardware/gralloc.h>
#include <camera/Camera.h>
#include <camera/CameraParameters.h>
#include <media/hardware/MetadataBufferType.h>

#include "gralloc_priv.h"
#include "exynos_format.h"
#include "csc.h"
#include "ExynosCamera.h"
#include "ExynosCameraVDis.h"
#include "ExynosCameraList.h"

#include <fcntl.h>
#include <sys/mman.h>

#include "ExynosCameraHWInterface.h"

#define GRALLOC_SET_USAGE_FOR_CAMERA \
    (GRALLOC_USAGE_SW_READ_NEVER | \
     GRALLOC_USAGE_SW_WRITE_OFTEN | \
     GRALLOC_USAGE_HW_TEXTURE | \
     GRALLOC_USAGE_HW_COMPOSER | \
     GRALLOC_USAGE_EXTERNAL_DISP)

#define GRALLOC_LOCK_FOR_CAMERA \
    (GRALLOC_USAGE_SW_READ_OFTEN)

//#define CAPTURE_DELAY

#define  JPEG_INPUT_COLOR_FMT           (V4L2_PIX_FMT_YUYV)

#define  NUM_OF_PREVIEW_BUF             (NUM_PREVIEW_BUFFERS)
#define  NUM_OF_VIDEO_BUF               (8)
#define  NUM_OF_PICTURE_BUF             (NUM_PICTURE_BUFFERS)
#define  NUM_OF_FLASH_BUF                 (3)
#define  NUM_OF_DEQUEUED_BUFFER         (3)
#define  NUM_OF_DETECTED_FACES          (16)
#define  NUM_OF_DETECTED_FACES_THRESHOLD (0)

//#define  CHECK_TIME_PREVIEW
//#define  CHECK_TIME_RECORDING
#define  CHECK_TIME_FRAME_DURATION      (10)

#define TRY_THREAD_STATUS_PREVIEW (0)
#define TRY_THREAD_STATUS_ISP (1)
#define TRY_THREAD_STATUS_SENSOR (2)
#define TRY_THREAD_STATUS_BAYER (3)

#ifdef SCALABLE_SENSOR
#define SCALABLE_SENSOR_THRESHOLD (10)
#endif

#define START_PREVIEW_WATING_TIME           (5000) /* 5msec */
#define START_PREVIEW_TOTAL_WATING_TIME  (5000000) /* 5000msec */

#define ON_SERVICE              (0)
#define ON_HAL                  (1)
#define ON_DRIVER               (2)

#ifdef CAPTURE_DELAY
int capture_delay = 0;
#endif

#define ERR_THREADHOLD 30
#define CHECK_THREADHOLD(cnt) \
    (cnt >= ERR_THREADHOLD) ? true : false

namespace android {

class ExynosCameraHWInterface;

class ExynosCameraHWImpl : public ExynosCameraHWInterface {
public:
    ExynosCameraHWImpl() : ExynosCameraHWInterface(){};
    ExynosCameraHWImpl(int cameraId, camera_device_t *dev);
    virtual             ~ExynosCameraHWImpl();

    void        setCallbacks(camera_notify_callback notify_cb,
                                     camera_data_callback data_cb,
                                     camera_data_timestamp_callback data_cb_timestamp,
                                     camera_request_memory get_memory,
                                     void *user);

    void        enableMsgType(int32_t msgType);
    void        disableMsgType(int32_t msgType);
    bool        msgTypeEnabled(int32_t msgType);

    /* startPreview(), stopPreview(), setParameters(), setPreviewWindows() must be excuted exclusively
       related lock is m_startStopLock; */
    status_t    startPreviewLocked();
    void        stopPreviewLocked();
    status_t    setParametersLocked(const CameraParameters& params);
    status_t    setPreviewWindowLocked(preview_stream_ops *w);

    bool        previewEnabled();

    status_t    storeMetaDataInBuffers(bool enable);

    status_t    startRecording();
    void        stopRecording();
    bool        recordingEnabled();
    void        releaseRecordingFrame(const void *opaque);

    status_t    autoFocus();
    status_t    cancelAutoFocus();

    status_t    takePicture();
    status_t    cancelPicture();

    CameraParameters  getParameters() const;
    status_t    sendCommand(int32_t command, int32_t arg1, int32_t arg2);

    void        release();

    status_t    dump(int fd) const;

    inline  int         getCameraId() const;

private:
    status_t    setParameters(const CameraParameters& params);
    status_t    setPreviewWindow(preview_stream_ops *w);
    status_t    startPreview();
    void        stopPreview();

private:
#ifdef START_HW_THREAD_ENABLE
    class StartCameraHwThreadA : public Thread {
        ExynosCameraHWImpl *mHardware;
    public:
        StartCameraHwThreadA(ExynosCameraHWImpl *hw): Thread(false), mHardware(hw) { }
        virtual void onFirstRef() {
            run("CameraStartThreadA", PRIORITY_DEFAULT);
        }
        virtual bool threadLoop() {
            mHardware->startCameraHwThreadFuncA();
            return true;
        }
    };

    class StartCameraHwThreadB : public Thread {
        ExynosCameraHWImpl *mHardware;
    public:
        StartCameraHwThreadB(ExynosCameraHWImpl *hw): Thread(false), mHardware(hw) { }
        virtual void onFirstRef() {
            run("CameraStartThreadB", PRIORITY_DEFAULT);
        }
        virtual bool threadLoop() {
            mHardware->startCameraHwThreadFuncB();
            return true;
        }
    };

    class StartCameraHwThreadC : public Thread {
        ExynosCameraHWImpl *mHardware;
    public:
        StartCameraHwThreadC(ExynosCameraHWImpl *hw): Thread(false), mHardware(hw) { }
        virtual void onFirstRef() {
            run("CameraStartThreadC", PRIORITY_DEFAULT);
        }
        virtual bool threadLoop() {
            mHardware->startCameraHwThreadFuncC();
            return true;
        }
    };
#endif

    class PreviewThread : public Thread {
        ExynosCameraHWImpl *mHardware;
    public:
        PreviewThread(ExynosCameraHWImpl *hw):
        Thread(false),
        mHardware(hw) { }
        virtual void onFirstRef() {
            run("CameraPreviewThread", PRIORITY_DEFAULT);
        }
        virtual bool threadLoop() {
            mHardware->m_previewThreadFuncWrapper();
            return false;
        }
    };
    class VideoThread : public Thread {
        ExynosCameraHWImpl *mHardware;
    public:
        VideoThread(ExynosCameraHWImpl *hw):
        Thread(false),
        mHardware(hw) { }
        virtual void onFirstRef() {
            run("CameraVideoThread", PRIORITY_DEFAULT);
        }
        virtual bool threadLoop() {
            mHardware->m_videoThreadFuncWrapper();
            return false;
        }
    };

    class PictureThread : public Thread {
        ExynosCameraHWImpl *mHardware;
    public:
        PictureThread(ExynosCameraHWImpl *hw):
        Thread(false),
        mHardware(hw) { }
        virtual bool threadLoop() {
            mHardware->m_pictureThreadFunc();
            return false;
        }
    };

    class SensorThreadLpzsl : public Thread {
        ExynosCameraHWImpl *mHardware;
    public:
        SensorThreadLpzsl(ExynosCameraHWImpl *hw):
        Thread(false),
        mHardware(hw) { }
        virtual void onFirstRef() {
            run("CameraSensorThreadLpzsl", PRIORITY_DEFAULT);
        }
        virtual bool threadLoop () {
            mHardware->m_sensorThreadFuncWrapLpzsl();
            return false;
        }
    };

    class ISPThread : public Thread {
        ExynosCameraHWImpl *mHardware;
    public:
        ISPThread(ExynosCameraHWImpl *hw): Thread(false), mHardware(hw) { }
        virtual void onFirstRef() {
            run("CameraISPThread", PRIORITY_DEFAULT);
        }
        virtual bool threadLoop() {
            mHardware->m_ispThreadFunc();
            return true;
        }
    };

    class ISPThread2 : public Thread {
        ExynosCameraHWImpl *mHardware;
    public:
        ISPThread2(ExynosCameraHWImpl *hw): Thread(false), mHardware(hw) { }
        virtual void onFirstRef() {
            run("CameraISP2Thread", PRIORITY_DEFAULT);
        }
        virtual bool threadLoop() {
            mHardware->m_ispThreadFunc2();
            return true;
        }
    };

    class AutoFocusThread : public Thread {
        ExynosCameraHWImpl *mHardware;
    public:
        AutoFocusThread(ExynosCameraHWImpl *hw): Thread(false), mHardware(hw) { }
        virtual void onFirstRef() {
            /* run("CameraAutoFocusThread", PRIORITY_DEFAULT); */
        }
        virtual bool threadLoop() {
            mHardware->m_autoFocusThreadFunc();
            return false;
        }
    };

    class SensorThread : public Thread {
        ExynosCameraHWImpl *mHardware;
    public:
        SensorThread(ExynosCameraHWImpl *hw):
        Thread(false),
        mHardware(hw) { }
        virtual void onFirstRef() {
            run("CameraSensorThread", PRIORITY_DEFAULT);
        }
        virtual bool threadLoop () {
            mHardware->m_sensorThreadFuncWrap();
            return false;
        }
    };

    class SensorThread2 : public Thread {
        ExynosCameraHWImpl *mHardware;
    public:
        SensorThread2(ExynosCameraHWImpl *hw):
        Thread(false),
        mHardware(hw) { }
        virtual void onFirstRef() {
            run("CameraSensorThread", PRIORITY_DEFAULT);
        }
        virtual bool threadLoop () {
            mHardware->m_sensorThreadFuncWrap2();
            return false;
        }
    };

    typedef bool (ExynosCameraHWImpl::*thread_loop)(void);
    class CameraThread : public Thread {
        ExynosCameraHWImpl *mHardware;
        thread_loop mThreadLoop;
        char mName[64];
        struct timeval mTimeStart;
        struct timeval mTimeStop;
    public:
        CameraThread(ExynosCameraHWImpl *hw, thread_loop loop) :
#ifdef SINGLE_PROCESS
            // In single process mode this thread needs to be a java thread,
            // since we won't be calling through the binder.
            Thread(true),
#else
            Thread(false),
#endif
            mHardware(hw),
            mThreadLoop(loop) {
            memset(&mTimeStart, 0, sizeof(mTimeStart));
            memset(&mTimeStop, 0, sizeof(mTimeStop));
            memset(&mName, 0, sizeof(mName));
        }

        virtual status_t run(const char* name = 0,
            int32_t priority = PRIORITY_DEFAULT,
            size_t stack = 0) {
            memset(&mTimeStart, 0, sizeof(mTimeStart));
            memset(&mTimeStop, 0, sizeof(mTimeStop));
            memset(&mName, 0, sizeof(mName));
            memcpy(mName, name, strlen(name) + 1);
            return Thread::run(name, priority, stack);
        }

        void calcFrameWaitTime(int maxFps) {
            // Calculate how long to wait between frames
            if (mTimeStart.tv_sec == 0 && mTimeStart.tv_usec == 0) {
                gettimeofday(&mTimeStart, NULL);
            }
            else {
                gettimeofday(&mTimeStop, NULL);
                unsigned long timeUs = (mTimeStop.tv_sec*1000000 + mTimeStop.tv_usec)
                    - (mTimeStart.tv_sec*1000000 + mTimeStart.tv_usec);
                gettimeofday(&mTimeStart, NULL);
                //unsigned long framerateUs = 1000.0/maxFps*1000000;
                //unsigned long delay = framerateUs > timeUs ? framerateUs - timeUs : 0;

                ALOGV("%s: time %ld us", mName, timeUs);
                //usleep(delay);
            }
        }

    private:
        virtual bool threadLoop() {
            // loop until we need to quit
            return (mHardware->*mThreadLoop)();
        }
    };



private:
    char    m_antiBanding[10];

    bool        m_initSecCamera(int cameraId);
    void        m_initDefaultParameters(int cameraId);

    void        m_disableMsgType(int32_t msgType, bool restore);
    void        m_restoreMsgType(void);

    status_t    m_startSensor();
    void        m_stopSensor();
    bool        m_sensorThreadFuncM2M(void);
    bool        m_sensorThreadFuncOTF(void);
    bool        m_sensorThreadFuncWrap(void);

    status_t    m_startSensor2();
    void        m_stopSensor2();
    bool        m_sensorThreadFunc2(void);
    bool        m_sensorThreadFuncWrap2(void);

    status_t    m_startSensorLpzsl();
    void        m_stopSensorLpzsl();
    bool        m_sensorThreadFuncLpzsl(void);
    bool        m_sensorThreadFuncWrapLpzsl(void);

#ifdef START_HW_THREAD_ENABLE
    bool        startCameraHwThreadFuncA(void);
    bool        startCameraHwThreadFuncB(void);
    bool        startCameraHwThreadFuncC(void);
#endif
    void        releaseBuffer(void);
    bool        getPreviewCallbackBuffer(void);
    bool        startCameraHw(void);
    bool        m_startPreviewInternal(void);
    void        m_stopPreviewInternal(void);
    bool        m_previewThreadFuncWrapper(void);
    bool        m_previewThreadFunc(void);

    bool        m_doPreviewToCallbackFunc(ExynosBuffer previewBuf, ExynosBuffer *callbackBuf, bool useCSC);
    bool        m_doCallbackToPreviewFunc(ExynosBuffer previewBuf, ExynosBuffer *callbackBuf, bool useCSC);

    bool        m_videoThreadFuncWrapper(void);
    bool        m_videoThreadFunc(void);
    bool        m_autoFocusThreadFunc(void);
    bool        m_ispThreadFunc(void);
    bool        m_ispThreadFunc2(void);

    bool        m_startPictureInternal(void);
    bool        m_stopPictureInternal(void);

    bool        m_startPictureInternal2(void);
    bool        m_stopPictureInternal2(void);

    bool        m_pictureThreadFunc(void);

    int         m_saveJpeg(unsigned char *real_jpeg, int jpeg_size);
    int         m_decodeInterleaveData(unsigned char *pInterleaveData,
                                       int interleaveDataSize,
                                       int yuvWidth,
                                       int yuvHeight,
                                       int *pJpegSize,
                                       void *pJpegData,
                                       void *pYuvData);
    bool        m_YUY2toNV21(void *srcBuf, void *dstBuf, uint32_t srcWidth, uint32_t srcHeight);
    bool        m_scaleDownYuv422(char *srcBuf, uint32_t srcWidth,
                                  uint32_t srcHight, char *dstBuf,
                                  uint32_t dstWidth, uint32_t dstHight);

    bool        m_checkVideoStartMarker(unsigned char *pBuf);
    bool        m_checkEOIMarker(unsigned char *pBuf);
    bool        m_findEOIMarkerInJPEG(unsigned char *pBuf,
                                      int dwBufSize, int *pnJPEGsize);
    bool        m_splitFrame(unsigned char *pFrame, int dwSize,
                             int dwJPEGLineLength, int dwVideoLineLength,
                             int dwVideoHeight, void *pJPEG,
                             int *pdwJPEGSize, void *pVideo,
                             int *pdwVideoSize);
    void        m_setSkipFrame(int frame);
    int         m_getSkipFrame();
    void        m_decSkipFrame();
    bool        m_isSupportedPreviewSize(const int width, const int height);
    bool        m_isSupportedPictureSize(const int width, const int height) const;
    bool        m_isSupportedVideoSize(const int width, const int height) const;

    int         m_getAlignedYUVSize(int colorFormat, int w, int h, ExynosBuffer *buf, bool flagAndroidColorFormat = false);

    bool        m_getSupportedFpsList(String8 & string8Buf, int min, int max);
    bool        m_getSupportedVariableFpsList(int min, int max, int *newMin, int *newMax);
    bool        m_getResolutionList(String8 & string8Buf, int *w, int *h, int mode);
    bool        m_getZoomRatioList(String8 & string8Buf, int maxZoom, int start, int end);
    bool        m_getMatchedPictureSize(const int src_w, const int src_h, int *dst_w, int *dst_h);

    int         m_bracketsStr2Ints(char *str, int num, ExynosRect2 *rect2s, int *weights, int mode);
    bool        m_subBracketsStr2Ints(int num, char *str, int *arr);
    int         m_calibratePosition(int w, int new_w, int x);

    bool        m_startPictureInternalLpzsl(void);
    bool        m_stopPictureInternalLpzsl(void);
    void        m_checkPreviewTime(void);
    void        m_checkRecordingTime(void);

    bool        m_checkPictureBufferVaild(ExynosBuffer *buf, int retry);
    void        m_resetRecordingFrameStatus(void);
    int         m_getRecordingFrame(void);
    void        m_freeRecordingFrame(int index);

    void        m_pushVideoQ(ExynosBuffer *buf);
    bool        m_popVideoQ(ExynosBuffer *buf);
    int         m_sizeOfVideoQ(void);
    void        m_releaseVideoQ(void);

    void        m_pushFrontPreviewQ(ExynosBuffer *buf);
    void        m_pushPreviewQ(ExynosBuffer *buf);
    bool        m_popPreviewQ(ExynosBuffer *buf);
    int         m_sizeOfPreviewQ(void);
    void        m_releasePreviewQ(void);
    bool        m_eraseBackPreviewQ(void);

    void        m_setPreviewBufStatus(int index, int status);

    bool        m_skipFrom3A1ToIsp(int skipCnt, int backFpsMin, int backFpsMax);

    mutable Mutex   m_startStopLock;
    bool        m_checkStartPreviewComplete(uint32_t mask);
    void        m_setStartPreviewComplete(int threadId, bool toggle);
    void        m_clearAllStartPreviewComplete(void);
#ifdef SCALABLE_SENSOR
    bool        m_chgScalableSensorSize(enum SCALABLE_SENSOR_SIZE sizeMode);
    bool        m_checkScalableSate(enum SCALABLE_SENSOR_SIZE sizeMode);
    bool        m_checkAndWaitScalableSate(enum SCALABLE_SENSOR_SIZE sizeMode);
#endif
private:
    enum MODE {
        MODE_PREVIEW = 0,
        MODE_PICTURE,
        MODE_VIDEO,
    };

    enum THREAD_ID {
        THREAD_ID_ALL_CLEARED = 0,
        THREAD_ID_SENSOR      = 1 << 0,
        THREAD_ID_PREVIEW     = 1 << 1,
        THREAD_ID_BAYER_OUT   = 1 << 2,
        THREAD_ID_ALL_SET     = (THREAD_ID_SENSOR | THREAD_ID_PREVIEW | THREAD_ID_BAYER_OUT)
    };

#ifdef START_HW_THREAD_ENABLE
    sp<StartCameraHwThreadA>      m_startCameraHwThreadA;
    sp<StartCameraHwThreadB>      m_startCameraHwThreadB;
    sp<StartCameraHwThreadC>      m_startCameraHwThreadC;
#endif
    sp<CameraThread>    m_previewThread;
    sp<VideoThread>     m_videoThread;
    sp<AutoFocusThread> m_autoFocusThread;
    sp<PictureThread>   m_pictureThread;
    sp<CameraThread>    m_sensorThread;
    sp<SensorThread2>    m_sensorThread2;
    sp<CameraThread>    m_sensorThreadLpzsl;
    sp<CameraThread> m_ispThread;
    sp<ISPThread2> m_ispThread2;

#ifdef START_HW_THREAD_ENABLE
    mutable Mutex       m_startCameraHwThreadLockA;
    mutable Condition   m_startCameraHwThreadConditionA;
    bool                m_startCameraHwThreadRunA;
    bool                m_exitStartCameraHwThreadA;
    bool                m_ErrorExistInCameraHwThreadA;

    mutable Mutex       m_startCameraHwThreadFinishLockA;
    mutable Condition   m_startCameraHwThreadFinishConditionA;

    mutable Mutex       m_startCameraHwThreadLockB;
    mutable Condition   m_startCameraHwThreadConditionB;
    bool                m_startCameraHwThreadRunningB;
    bool                m_exitStartCameraHwThreadB;
    bool                m_ErrorExistInCameraHwThreadB;

    mutable Mutex       m_startCameraHwThreadFinishLockB;
    mutable Condition   m_startCameraHwThreadFinishConditionB;
    bool                m_CameraHwThreadFinishedB;
    bool                m_CameraHwThreadFinishWaitingB;

    mutable Mutex       m_startCameraHwThreadLockC;
    mutable Condition   m_startCameraHwThreadConditionC;
    bool                m_exitStartCameraHwThreadC;
    bool                m_ErrorExistInCameraHwThreadC;

    mutable Mutex       m_initCameraBufferAllocFinishLock;
    mutable Condition   m_initCameraBufferAllocFinishCondition;
    bool                m_CameraBufferAllocFinished;
    bool                m_CameraBufferAllocWaiting;
#endif

    /* used by auto focus thread to block until it's told to run */
    mutable Mutex       m_autoFocusLock;
    bool                m_exitAutoFocusThread;
    bool                m_autoFocusRunning;

    mutable Mutex       m_ispLock;
    mutable Condition   m_ispCondition;
    bool        m_exitIspThread;

    mutable Mutex       m_ispLock2;
    mutable Condition   m_ispCondition2;
    bool        m_exitIspThread2;

    /* used by preview thread to block until it's told to run */
    mutable Mutex       m_previewLock;
    mutable Mutex       m_previewStopLock;
    mutable Condition   m_previewCondition;
    mutable Condition   m_previewStoppedCondition;
#ifdef USE_CAMERA_ESD_RESET
            bool        m_sensorESDReset;
#endif
            bool        m_previewRunning;
            bool        m_exitPreviewThread;
            bool        m_previewStartDeferred;
    unsigned int        m_startComplete;

    mutable Mutex       m_videoLock;
    mutable Condition   m_videoCondition;
    mutable Condition   m_videoStoppedCondition;
            bool        m_videoRunning;
            bool        m_exitVideoThread;

    mutable Mutex       m_sensorStopLock;
    mutable Mutex       m_sensorLock;
    mutable Condition   m_sensorCondition;
    mutable Condition   m_sensorStoppedCondition;
    bool                m_sensorRunning;
    bool                m_exitSensorThread;

    mutable Mutex       m_sensorStopLock2;
    mutable Mutex       m_sensorLock2;
    mutable Condition   m_sensorCondition2;
    mutable Condition   m_sensorStoppedCondition2;
    bool                m_sensorRunning2;
    bool                m_exitSensorThread2;

    mutable Mutex       m_sensorStopLockLpzsl;
    mutable Mutex       m_sensorLockLpzsl;
    mutable Condition   m_sensorConditionLpzsl;
    mutable Condition   m_sensorStoppedConditionLpzsl;
    bool                m_sensorRunningLpzsl;
    bool                m_exitSensorThreadLpzsl;

    void               *m_grallocVirtAddr[NUM_OF_PREVIEW_BUF];
    int                 m_matchedGrallocIndex[NUM_OF_PREVIEW_BUF];
    nsecs_t             m_videoBufTimestamp[NUM_OF_PREVIEW_BUF];
    ExynosBuffer        m_pictureBuf[NUM_OF_FLASH_BUF];
    ExynosBuffer        m_pictureBuf2;

    ExynosBuffer        m_previewBuf2;
    ExynosBuffer        m_callbackBuf2;

    ExynosBuffer        m_sharedBayerBuffer;
    ExynosBuffer        m_sharedBayerBuffer2;
    ExynosBuffer        m_sharedISPBuffer;
    ExynosBuffer        m_sharedISPBuffer2;
    mutable Mutex       m_pictureLock;
    mutable Condition   m_pictureCondition;
            bool        m_pictureRunning;
            bool        m_pictureRunning2;
            bool        m_captureInProgress;
            bool        m_captureMode;
            bool        m_waitForCapture;

    ExynosRect          m_orgPreviewRect;
    ExynosRect          m_orgPictureRect;
    ExynosRect          m_orgVideoRect;

    void               *m_exynosPreviewCSC;
    void               *m_exynosPictureCSC;
    void               *m_exynosVideoCSC;

    int                 m_flip_horizontal;
    bool                m_isCSCBypassed;

    preview_stream_ops *m_previewWindow;

    int                 m_numOfDequeuedBuf;

    /* used to guard threading state */
    mutable Mutex       m_stateLock;

    CameraParameters    m_params;
    CameraParameters    m_internalParams;

    int                 m_numOfCamera;

    camera_memory_t    *m_previewCallbackHeap[NUM_OF_PREVIEW_BUF];

    buffer_handle_t    *m_previewBufHandle[NUM_OF_PREVIEW_BUF];
    int                 m_previewStride[NUM_OF_PREVIEW_BUF];
    bool                m_avaliblePreviewBufHandle[NUM_OF_PREVIEW_BUF];
    bool                m_flagGrallocLocked[NUM_OF_PREVIEW_BUF];
    int                 m_previewBufStatus[NUM_OF_PREVIEW_BUF];
    bool                m_previewBufRegistered[NUM_OF_PREVIEW_BUF];

    int                 m_minUndequeuedBufs;

    int                 m_recordingFrameIndex;
    nsecs_t             m_lastRecordingTimestamp;
    nsecs_t             m_recordingStartTimestamp;

    Mutex               m_videoQMutex;
    List<ExynosBuffer>  m_videoQ;

    Mutex               m_previewQMutex;
    List<ExynosBuffer>  m_previewQ;

    camera_memory_t    *m_recordHeap;
    camera_memory_t    *m_videoHeap[NUM_OF_VIDEO_BUF];
    camera_memory_t    *m_resizedVideoHeap[NUM_OF_VIDEO_BUF][2];

    camera_memory_t    *m_pictureHeap[NUM_OF_PICTURE_BUF];
    camera_memory_t    *m_pictureHeap2[NUM_OF_PICTURE_BUF];
    camera_memory_t    *m_rawHeap;
    int                 m_rawHeapSize;

    camera_memory_t    *m_jpegHeap;
    int                 m_jpegHeapFd;

    bool                m_callbackCSC;

    int                 m_previewCallbackHeapFd[NUM_OF_PREVIEW_BUF];
    int                 m_recordHeapFd;
    int                 m_videoHeapFd[NUM_OF_VIDEO_BUF];
    int                 m_resizedVideoHeapFd[NUM_OF_VIDEO_BUF][2];
    bool                m_recordingFrameAvailable[NUM_OF_VIDEO_BUF];
    int                 m_pictureHeapFd[NUM_OF_PICTURE_BUF];
    int                 m_pictureHeap2Fd[NUM_OF_PICTURE_BUF];
    int                 m_rawHeapFd;

    camera_frame_metadata_t  m_frameMetadata;
    camera_face_t            m_faces[NUM_OF_DETECTED_FACES];
    bool                     m_faceDetected;
    int                      m_fdThreshold;

    int                 m_flashMode;
    int                 m_previewCount;
    int                 m_availableRecordingFrameCnt;
    Mutex               m_recordingFrameMutex;

#ifdef CHECK_TIME_PREVIEW
    DurationTimer       m_previewTimer;
#endif
    long long           m_previewTimerTime[CHECK_TIME_FRAME_DURATION];
    int                 m_previewTimerIndex;
#ifdef CHECK_TIME_RECORDING
    DurationTimer       m_recordingTimer;
#endif
    long long           m_recordingTimerTime[CHECK_TIME_FRAME_DURATION];
    int                 m_recordingTimerIndex;

    int                 m_sensorErrCnt;

    ExynosCamera       *m_secCamera;
#ifdef USE_VDIS
    ExynosCameraVDis   *m_VDis;
#endif

    mutable Mutex       m_skipFrameLock;
            int         m_skipFrame;

    camera_notify_callback     m_notifyCb;
    camera_data_callback       m_dataCb;
    camera_data_timestamp_callback m_dataCbTimestamp;
    camera_request_memory      m_getMemoryCb;
    void                      *m_callbackCookie;

            int32_t     m_msgEnabled;
            int32_t     m_storedMsg;

    camera_device_t *m_halDevice;
    static gralloc_module_t const* m_grallocHal;
#ifdef MULTI_INSTANCE_CHECK
    static int multi_instance_check;
#endif
    static Mutex isCh0Mutex;
    static Mutex is3aaMutex;
    static int isp_check;

    int isp_input_count;
    int isp_input_count2;
    int isp_last_frame_cnt;

    int m_cameraId;

    unsigned int m_sharedBayerFcount;
#ifdef FORCE_LEADER_OFF
    bool tryThreadStop;
    int tryThreadStatus;
    bool leaderOff;
#endif
#ifdef DYNAMIC_BAYER_BACK_REC
    bool isDqSensor;
#endif
#ifdef SCALABLE_SENSOR
#ifndef DYNAMIC_BAYER_BACK_REC
    bool isDqSensor;
#endif
    bool         m_13MCaptureStart;
    Mutex        m_13MCaptureLock;
#endif

    bool         m_forceAELock;
};

}; // namespace android

#endif
