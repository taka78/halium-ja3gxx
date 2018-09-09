/*
 *
 * Copyright 2012 Samsung Electronics S.LSI Co. LTD
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * @file      Exynos_OMX_Aacdec.c
 * @brief
 * @author    Sungyeon Kim (sy85.kim@samsung.com)
 * @version   1.0.0
 * @history
 *   2012.12.22 : Create
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Exynos_OMX_Macros.h"
#include "Exynos_OMX_Basecomponent.h"
#include "Exynos_OMX_Baseport.h"
#include "Exynos_OMX_Adec.h"
#include "Exynos_OSAL_ETC.h"
#include "Exynos_OSAL_Semaphore.h"
#include "Exynos_OSAL_Thread.h"
#include "library_register.h"
#include "Exynos_OMX_Aacdec.h"

#undef  EXYNOS_LOG_TAG
#define EXYNOS_LOG_TAG    "EXYNOS_AAC_DEC"
#define EXYNOS_LOG_OFF
#include "Exynos_OSAL_Log.h"

//#define Seiren_DUMP_TO_FILE
#ifdef Seiren_DUMP_TO_FILE
#include "stdio.h"

FILE *inFile;
FILE *outFile;
#endif

OMX_ERRORTYPE Exynos_Seiren_AacDec_GetParameter(
    OMX_IN    OMX_HANDLETYPE hComponent,
    OMX_IN    OMX_INDEXTYPE  nParamIndex,
    OMX_INOUT OMX_PTR        pComponentParameterStructure)
{
    OMX_ERRORTYPE             ret = OMX_ErrorNone;
    OMX_COMPONENTTYPE        *pOMXComponent = NULL;
    EXYNOS_OMX_BASECOMPONENT *pExynosComponent = NULL;

    FunctionIn();

    if (hComponent == NULL || pComponentParameterStructure == NULL) {
        ret = OMX_ErrorBadParameter;
        goto EXIT;
    }
    pOMXComponent = (OMX_COMPONENTTYPE *)hComponent;
    ret = Exynos_OMX_Check_SizeVersion(pOMXComponent, sizeof(OMX_COMPONENTTYPE));
    if (ret != OMX_ErrorNone) {
        goto EXIT;
    }
    if (pOMXComponent->pComponentPrivate == NULL) {
        ret = OMX_ErrorBadParameter;
        goto EXIT;
    }

    pExynosComponent = (EXYNOS_OMX_BASECOMPONENT *)pOMXComponent->pComponentPrivate;
    if (pExynosComponent->currentState == OMX_StateInvalid ) {
        ret = OMX_ErrorInvalidState;
        goto EXIT;
    }

    switch (nParamIndex) {
    case OMX_IndexParamAudioAac:
    {
        OMX_AUDIO_PARAM_AACPROFILETYPE *pDstAacParam = (OMX_AUDIO_PARAM_AACPROFILETYPE *)pComponentParameterStructure;
        OMX_AUDIO_PARAM_AACPROFILETYPE *pSrcAacParam = NULL;
        EXYNOS_AAC_HANDLE       *pAacDec = NULL;

        ret = Exynos_OMX_Check_SizeVersion(pDstAacParam, sizeof(OMX_AUDIO_PARAM_AACPROFILETYPE));
        if (ret != OMX_ErrorNone) {
            goto EXIT;
        }

        if (pDstAacParam->nPortIndex >= ALL_PORT_NUM) {
            ret = OMX_ErrorBadPortIndex;
            goto EXIT;
        }

        pAacDec = (EXYNOS_AAC_HANDLE *)((EXYNOS_OMX_AUDIODEC_COMPONENT *)pExynosComponent->hComponentHandle)->hCodecHandle;
        pSrcAacParam = &pAacDec->aacParam;

        Exynos_OSAL_Memcpy(pDstAacParam, pSrcAacParam, sizeof(OMX_AUDIO_PARAM_AACPROFILETYPE));
    }
        break;
    case OMX_IndexParamAudioPcm:
    {
        OMX_AUDIO_PARAM_PCMMODETYPE *pDstPcmParam = (OMX_AUDIO_PARAM_PCMMODETYPE *)pComponentParameterStructure;
        OMX_AUDIO_PARAM_PCMMODETYPE *pSrcPcmParam = NULL;
        EXYNOS_AAC_HANDLE           *pAacDec = NULL;

        ret = Exynos_OMX_Check_SizeVersion(pDstPcmParam, sizeof(OMX_AUDIO_PARAM_PCMMODETYPE));
        if (ret != OMX_ErrorNone) {
            goto EXIT;
        }

        if (pDstPcmParam->nPortIndex >= ALL_PORT_NUM) {
            ret = OMX_ErrorBadPortIndex;
            goto EXIT;
        }

        pAacDec = (EXYNOS_AAC_HANDLE *)((EXYNOS_OMX_AUDIODEC_COMPONENT *)pExynosComponent->hComponentHandle)->hCodecHandle;
        pSrcPcmParam = &pAacDec->pcmParam;

        Exynos_OSAL_Memcpy(pDstPcmParam, pSrcPcmParam, sizeof(OMX_AUDIO_PARAM_PCMMODETYPE));
    }
        break;
    case OMX_IndexParamStandardComponentRole:
    {
        OMX_S32 codecType;
        OMX_PARAM_COMPONENTROLETYPE *pComponentRole = (OMX_PARAM_COMPONENTROLETYPE *)pComponentParameterStructure;

        ret = Exynos_OMX_Check_SizeVersion(pComponentRole, sizeof(OMX_PARAM_COMPONENTROLETYPE));
        if (ret != OMX_ErrorNone) {
            goto EXIT;
        }

        Exynos_OSAL_Strcpy((char *)pComponentRole->cRole, EXYNOS_OMX_COMPONENT_AAC_DEC_ROLE);
    }
        break;
    default:
        ret = Exynos_OMX_AudioDecodeGetParameter(hComponent, nParamIndex, pComponentParameterStructure);
        break;
    }
EXIT:
    FunctionOut();

    return ret;
}

OMX_ERRORTYPE Exynos_Seiren_AacDec_SetParameter(
    OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_INDEXTYPE  nIndex,
    OMX_IN OMX_PTR        pComponentParameterStructure)
{
    OMX_ERRORTYPE             ret = OMX_ErrorNone;
    OMX_COMPONENTTYPE        *pOMXComponent = NULL;
    EXYNOS_OMX_BASECOMPONENT *pExynosComponent = NULL;

    FunctionIn();

    if (hComponent == NULL || pComponentParameterStructure == NULL) {
        ret = OMX_ErrorBadParameter;
        goto EXIT;
    }
    pOMXComponent = (OMX_COMPONENTTYPE *)hComponent;
    ret = Exynos_OMX_Check_SizeVersion(pOMXComponent, sizeof(OMX_COMPONENTTYPE));
    if (ret != OMX_ErrorNone) {
        goto EXIT;
    }
    if (pOMXComponent->pComponentPrivate == NULL) {
        ret = OMX_ErrorBadParameter;
        goto EXIT;
    }

    pExynosComponent = (EXYNOS_OMX_BASECOMPONENT *)pOMXComponent->pComponentPrivate;
    if (pExynosComponent->currentState == OMX_StateInvalid ) {
        ret = OMX_ErrorInvalidState;
        goto EXIT;
    }

    switch (nIndex) {
    case OMX_IndexParamAudioAac:
    {
        OMX_AUDIO_PARAM_AACPROFILETYPE *pDstAacParam = NULL;
        OMX_AUDIO_PARAM_AACPROFILETYPE *pSrcAacParam = (OMX_AUDIO_PARAM_AACPROFILETYPE *)pComponentParameterStructure;
        EXYNOS_AAC_HANDLE       *pAacDec = NULL;

        ret = Exynos_OMX_Check_SizeVersion(pSrcAacParam, sizeof(OMX_AUDIO_PARAM_AACPROFILETYPE));
        if (ret != OMX_ErrorNone) {
            goto EXIT;
        }

        if (pSrcAacParam->nPortIndex >= ALL_PORT_NUM) {
            ret = OMX_ErrorBadPortIndex;
            goto EXIT;
        }

        pAacDec = (EXYNOS_AAC_HANDLE *)((EXYNOS_OMX_AUDIODEC_COMPONENT *)pExynosComponent->hComponentHandle)->hCodecHandle;
        pDstAacParam = &pAacDec->aacParam;

        Exynos_OSAL_Memcpy(pDstAacParam, pSrcAacParam, sizeof(OMX_AUDIO_PARAM_AACPROFILETYPE));
        Exynos_OSAL_Log(EXYNOS_LOG_TRACE, "\e[1;33;46m nSize : %d  \e[0m", pDstAacParam->nSize);
        Exynos_OSAL_Log(EXYNOS_LOG_TRACE, "\e[1;33;46m nPortIndex : %d  \e[0m", pDstAacParam->nPortIndex);
        Exynos_OSAL_Log(EXYNOS_LOG_TRACE, "\e[1;33;46m nChannels : %d  \e[0m", pDstAacParam->nChannels);
        Exynos_OSAL_Log(EXYNOS_LOG_TRACE, "\e[1;33;46m nSampleRate : %d  \e[0m", pDstAacParam->nSampleRate);
        Exynos_OSAL_Log(EXYNOS_LOG_TRACE, "\e[1;33;46m nBitRate : %d  \e[0m", pDstAacParam->nBitRate);
        Exynos_OSAL_Log(EXYNOS_LOG_TRACE, "\e[1;33;46m nAudioBandWidth : %d  \e[0m", pDstAacParam->nAudioBandWidth);
        Exynos_OSAL_Log(EXYNOS_LOG_TRACE, "\e[1;33;46m nFrameLength : %d  \e[0m", pDstAacParam->nFrameLength);
        Exynos_OSAL_Log(EXYNOS_LOG_TRACE, "\e[1;33;46m nAACtools : %d  \e[0m", pDstAacParam->nAACtools);
        Exynos_OSAL_Log(EXYNOS_LOG_TRACE, "\e[1;33;46m nAACERtools : %d  \e[0m", pDstAacParam->nAACERtools);
        Exynos_OSAL_Log(EXYNOS_LOG_TRACE, "\e[1;33;46m eAACProfile : %d  \e[0m", pDstAacParam->eAACProfile);
        Exynos_OSAL_Log(EXYNOS_LOG_TRACE, "\e[1;33;46m eAACStreamFormat : %d  \e[0m", pDstAacParam->eAACStreamFormat);
        Exynos_OSAL_Log(EXYNOS_LOG_TRACE, "\e[1;33;46m eChannelMode : %d  \e[0m", pDstAacParam->eChannelMode);
    }
        break;
    case OMX_IndexParamAudioPcm:
    {
        OMX_AUDIO_PARAM_PCMMODETYPE *pDstPcmParam = NULL;
        OMX_AUDIO_PARAM_PCMMODETYPE *pSrcPcmParam = (OMX_AUDIO_PARAM_PCMMODETYPE *)pComponentParameterStructure;
        EXYNOS_AAC_HANDLE           *pAacDec = NULL;

        ret = Exynos_OMX_Check_SizeVersion(pSrcPcmParam, sizeof(OMX_AUDIO_PARAM_PCMMODETYPE));
        if (ret != OMX_ErrorNone) {
            goto EXIT;
        }

        if (pSrcPcmParam->nPortIndex >= ALL_PORT_NUM) {
            ret = OMX_ErrorBadPortIndex;
            goto EXIT;
        }

        pAacDec = (EXYNOS_AAC_HANDLE *)((EXYNOS_OMX_AUDIODEC_COMPONENT *)pExynosComponent->hComponentHandle)->hCodecHandle;
        pDstPcmParam = &pAacDec->pcmParam;

        Exynos_OSAL_Memcpy(pDstPcmParam, pSrcPcmParam, sizeof(OMX_AUDIO_PARAM_PCMMODETYPE));
    }
        break;
    case OMX_IndexParamStandardComponentRole:
    {
        OMX_PARAM_COMPONENTROLETYPE *pComponentRole = (OMX_PARAM_COMPONENTROLETYPE*)pComponentParameterStructure;

        ret = Exynos_OMX_Check_SizeVersion(pComponentRole, sizeof(OMX_PARAM_COMPONENTROLETYPE));
        if (ret != OMX_ErrorNone) {
            goto EXIT;
        }

        if ((pExynosComponent->currentState != OMX_StateLoaded) && (pExynosComponent->currentState != OMX_StateWaitForResources)) {
            ret = OMX_ErrorIncorrectStateOperation;
            goto EXIT;
        }

        if (!Exynos_OSAL_Strcmp((char*)pComponentRole->cRole, EXYNOS_OMX_COMPONENT_AAC_DEC_ROLE)) {
            pExynosComponent->pExynosPort[INPUT_PORT_INDEX].portDefinition.format.audio.eEncoding = OMX_AUDIO_CodingAAC;
        } else {
            ret = OMX_ErrorBadParameter;
            goto EXIT;
        }
    }
        break;
    default:
        ret = Exynos_OMX_AudioDecodeSetParameter(hComponent, nIndex, pComponentParameterStructure);
        break;
    }
EXIT:
    FunctionOut();

    return ret;
}

OMX_ERRORTYPE Exynos_Seiren_AacDec_GetConfig(
    OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_INDEXTYPE  nIndex,
    OMX_IN OMX_PTR        pComponentConfigStructure)
{
    OMX_ERRORTYPE             ret = OMX_ErrorNone;
    OMX_COMPONENTTYPE        *pOMXComponent = NULL;
    EXYNOS_OMX_BASECOMPONENT *pExynosComponent = NULL;

    FunctionIn();

    if (hComponent == NULL || pComponentConfigStructure == NULL) {
        ret = OMX_ErrorBadParameter;
        goto EXIT;
    }
    pOMXComponent = (OMX_COMPONENTTYPE *)hComponent;
    ret = Exynos_OMX_Check_SizeVersion(pOMXComponent, sizeof(OMX_COMPONENTTYPE));
    if (ret != OMX_ErrorNone) {
        goto EXIT;
    }
    if (pOMXComponent->pComponentPrivate == NULL) {
        ret = OMX_ErrorBadParameter;
        goto EXIT;
    }

    pExynosComponent = (EXYNOS_OMX_BASECOMPONENT *)pOMXComponent->pComponentPrivate;
    if (pExynosComponent->currentState == OMX_StateInvalid) {
        ret = OMX_ErrorInvalidState;
        goto EXIT;
    }

    switch (nIndex) {
    default:
        ret = Exynos_OMX_AudioDecodeGetConfig(hComponent, nIndex, pComponentConfigStructure);
        break;
    }

EXIT:
    FunctionOut();

    return ret;
}

OMX_ERRORTYPE Exynos_Seiren_AacDec_SetConfig(
    OMX_IN OMX_HANDLETYPE hComponent,
    OMX_IN OMX_INDEXTYPE  nIndex,
    OMX_IN OMX_PTR        pComponentConfigStructure)
{
    OMX_ERRORTYPE             ret = OMX_ErrorNone;
    OMX_COMPONENTTYPE        *pOMXComponent = NULL;
    EXYNOS_OMX_BASECOMPONENT *pExynosComponent = NULL;

    FunctionIn();

    if (hComponent == NULL || pComponentConfigStructure == NULL) {
        ret = OMX_ErrorBadParameter;
        goto EXIT;
    }
    pOMXComponent = (OMX_COMPONENTTYPE *)hComponent;
    ret = Exynos_OMX_Check_SizeVersion(pOMXComponent, sizeof(OMX_COMPONENTTYPE));
    if (ret != OMX_ErrorNone) {
        goto EXIT;
    }
    if (pOMXComponent->pComponentPrivate == NULL) {
        ret = OMX_ErrorBadParameter;
        goto EXIT;
    }

    pExynosComponent = (EXYNOS_OMX_BASECOMPONENT *)pOMXComponent->pComponentPrivate;
    if (pExynosComponent->currentState == OMX_StateInvalid) {
        ret = OMX_ErrorInvalidState;
        goto EXIT;
    }

    switch (nIndex) {
    default:
        ret = Exynos_OMX_AudioDecodeSetConfig(hComponent, nIndex, pComponentConfigStructure);
        break;
    }

EXIT:
    FunctionOut();

    return ret;
}

OMX_ERRORTYPE Exynos_Seiren_AacDec_GetExtensionIndex(
    OMX_IN OMX_HANDLETYPE  hComponent,
    OMX_IN OMX_STRING      cParameterName,
    OMX_OUT OMX_INDEXTYPE *pIndexType)
{
    OMX_ERRORTYPE             ret = OMX_ErrorNone;
    OMX_COMPONENTTYPE        *pOMXComponent = NULL;
    EXYNOS_OMX_BASECOMPONENT *pExynosComponent = NULL;

    FunctionIn();

    if (hComponent == NULL) {
        ret = OMX_ErrorBadParameter;
        goto EXIT;
    }
    pOMXComponent = (OMX_COMPONENTTYPE *)hComponent;
    ret = Exynos_OMX_Check_SizeVersion(pOMXComponent, sizeof(OMX_COMPONENTTYPE));
    if (ret != OMX_ErrorNone) {
        goto EXIT;
    }

    if (pOMXComponent->pComponentPrivate == NULL) {
        ret = OMX_ErrorBadParameter;
        goto EXIT;
    }
    pExynosComponent = (EXYNOS_OMX_BASECOMPONENT *)pOMXComponent->pComponentPrivate;

    if ((cParameterName == NULL) || (pIndexType == NULL)) {
        ret = OMX_ErrorBadParameter;
        goto EXIT;
    }
    if (pExynosComponent->currentState == OMX_StateInvalid) {
        ret = OMX_ErrorInvalidState;
        goto EXIT;
    }

    ret = Exynos_OMX_AudioDecodeGetExtensionIndex(hComponent, cParameterName, pIndexType);

EXIT:
    FunctionOut();

    return ret;
}

OMX_ERRORTYPE Exynos_Seiren_AacDec_ComponentRoleEnum(
    OMX_IN  OMX_HANDLETYPE hComponent,
    OMX_OUT OMX_U8        *cRole,
    OMX_IN  OMX_U32        nIndex)
{
    OMX_ERRORTYPE               ret = OMX_ErrorNone;
    OMX_COMPONENTTYPE          *pOMXComponent = NULL;
    EXYNOS_OMX_BASECOMPONENT   *pExynosComponent = NULL;
    OMX_S32                     codecType;

    FunctionIn();

    if ((hComponent == NULL) || (cRole == NULL)) {
        ret = OMX_ErrorBadParameter;
        goto EXIT;
    }
    if (nIndex != (MAX_COMPONENT_ROLE_NUM - 1)) {
        ret = OMX_ErrorNoMore;
        goto EXIT;
    }
    pOMXComponent = (OMX_COMPONENTTYPE *)hComponent;
    ret = Exynos_OMX_Check_SizeVersion(pOMXComponent, sizeof(OMX_COMPONENTTYPE));
    if (ret != OMX_ErrorNone) {
        goto EXIT;
    }
    if (pOMXComponent->pComponentPrivate == NULL) {
        ret = OMX_ErrorBadParameter;
        goto EXIT;
    }

    pExynosComponent = (EXYNOS_OMX_BASECOMPONENT *)pOMXComponent->pComponentPrivate;
    if (pExynosComponent->currentState == OMX_StateInvalid ) {
        ret = OMX_ErrorInvalidState;
        goto EXIT;
    }

    Exynos_OSAL_Strcpy((char *)cRole, EXYNOS_OMX_COMPONENT_AAC_DEC_ROLE);

EXIT:
    FunctionOut();

    return ret;
}

OMX_ERRORTYPE Exynos_Seiren_AacDec_Init(OMX_COMPONENTTYPE *pOMXComponent)
{
    OMX_ERRORTYPE                  ret = OMX_ErrorNone;
    EXYNOS_OMX_BASECOMPONENT      *pExynosComponent = (EXYNOS_OMX_BASECOMPONENT *)pOMXComponent->pComponentPrivate;
    EXYNOS_OMX_AUDIODEC_COMPONENT *pAudioDec = (EXYNOS_OMX_AUDIODEC_COMPONENT *)pExynosComponent->hComponentHandle;
    EXYNOS_AAC_HANDLE             *pAacDec = (EXYNOS_AAC_HANDLE *)pAudioDec->hCodecHandle;

    FunctionIn();

    Exynos_OSAL_Memset(pExynosComponent->timeStamp, -19771003, sizeof(OMX_TICKS) * MAX_TIMESTAMP);
    Exynos_OSAL_Memset(pExynosComponent->nFlags, 0, sizeof(OMX_U32) * MAX_FLAGS);
    pExynosComponent->bUseFlagEOF = OMX_TRUE; /* Aac extractor should parse into frame unit. */
    pExynosComponent->bSaveFlagEOS = OMX_FALSE;
    pAacDec->hSeirenAacHandle.bConfiguredSeiren = OMX_FALSE;
    pAacDec->hSeirenAacHandle.bSeirenSendEOS = OMX_FALSE;
    pExynosComponent->getAllDelayBuffer = OMX_FALSE;

#ifdef Seiren_DUMP_TO_FILE
    inFile = fopen("/data/InFile.aac", "w+");
    outFile = fopen("/data/OutFile.pcm", "w+");
#endif

EXIT:
    FunctionOut();

    return ret;
}

OMX_ERRORTYPE Exynos_Seiren_AacDec_Terminate(OMX_COMPONENTTYPE *pOMXComponent)
{
    OMX_ERRORTYPE                  ret = OMX_ErrorNone;
    EXYNOS_OMX_BASECOMPONENT      *pExynosComponent = (EXYNOS_OMX_BASECOMPONENT *)pOMXComponent->pComponentPrivate;

    FunctionIn();

#ifdef Seiren_DUMP_TO_FILE
    fclose(inFile);
    fclose(outFile);
#endif

EXIT:
    FunctionOut();

    return ret;
}

OMX_ERRORTYPE Exynos_Seiren_Aac_Decode_Block(OMX_COMPONENTTYPE *pOMXComponent, EXYNOS_OMX_DATA *pInputData, EXYNOS_OMX_DATA *pOutputData)
{
    OMX_ERRORTYPE                  ret = OMX_ErrorNone;
    EXYNOS_OMX_BASECOMPONENT      *pExynosComponent = (EXYNOS_OMX_BASECOMPONENT *)pOMXComponent->pComponentPrivate;
    EXYNOS_OMX_AUDIODEC_COMPONENT *pAudioDec = (EXYNOS_OMX_AUDIODEC_COMPONENT *)pExynosComponent->hComponentHandle;
    EXYNOS_AAC_HANDLE             *pAacDec = (EXYNOS_AAC_HANDLE *)pAudioDec->hCodecHandle;
    int                            returnCodec = 0;
    unsigned long                  isSeirenStopped = 0;
    OMX_BOOL                       isSeirenIbufOverflow = OMX_FALSE;

    u32 fd = pAacDec->hSeirenAacHandle.hSeirenHandle;
    audio_mem_info_t input_mem_pool = pAacDec->hSeirenAacHandle.input_mem_pool;
    audio_mem_info_t output_mem_pool = pAacDec->hSeirenAacHandle.output_mem_pool;
    unsigned long sample_rate, channels;
    int consumed_size = 0;
    sample_rate = channels = 0;

    FunctionIn();

#ifdef Seiren_DUMP_TO_FILE
    if (pExynosComponent->reInputData == OMX_FALSE) {
        fwrite(pInputData->multiPlaneBuffer.dataBuffer[AUDIO_DATA_PLANE], pInputData->dataLen, 1, inFile);
    }
#endif

    /* Save timestamp and flags of input data */
    pOutputData->timeStamp = pInputData->timeStamp;
    pOutputData->nFlags = pInputData->nFlags & (~OMX_BUFFERFLAG_EOS);

    /* Decoding aac frames by Seiren */
    if (pExynosComponent->getAllDelayBuffer == OMX_FALSE) {
        input_mem_pool.data_size = pInputData->dataLen;
        char* pt = input_mem_pool.virt_addr;
        Exynos_OSAL_Log(EXYNOS_LOG_TRACE, "\e[1;33m %02X %02X %02X %02X %02X %02X %lld \e[0m", *pt,*(pt+1),*(pt+2),*(pt+3),*(pt+4), *(pt+5), pInputData->timeStamp);

        if (pInputData->nFlags & OMX_BUFFERFLAG_CODECCONFIG) {
            ADec_ConfigSignal(fd);
            unsigned char sample_rate_index = ((*(pt+1)) >> 7 & 0x01) |
                                              ((*pt)     << 1 & 0x0e);
            unsigned char num_of_channel = ((*(pt+1)) >> 3 & 0x07);
            Exynos_OSAL_Log(EXYNOS_LOG_TRACE, "index %x ", sample_rate_index);
            ADec_SetParams(fd, PCM_PARAM_SAMPLE_RATE, aac_sample_rates[sample_rate_index]);
            ADec_SetParams(fd, PCM_PARAM_NUM_OF_CH, num_of_channel);
            ADec_SendStream(fd, &input_mem_pool, &consumed_size);
            goto EXIT;
        }
        returnCodec = ADec_SendStream(fd, &input_mem_pool, &consumed_size);

        Exynos_OSAL_Log(EXYNOS_LOG_TRACE, "ProcessedSize : %d    return : %d", consumed_size, returnCodec);
        if (pInputData->nFlags & OMX_BUFFERFLAG_EOS)
            Exynos_OSAL_Log(EXYNOS_LOG_TRACE, "EOS!!");
        if (returnCodec >= 0) {
            if (pInputData->nFlags & OMX_BUFFERFLAG_EOS) {
                ADec_SendEOS(fd);
                pAacDec->hSeirenAacHandle.bSeirenSendEOS = OMX_TRUE;
            }
        } else if (returnCodec < 0) {
            ret = OMX_ErrorCodecDecode;
            goto EXIT;
        }
    }

    if (pAacDec->hSeirenAacHandle.bConfiguredSeiren == OMX_FALSE) {
        if ((pInputData->dataLen <= 0) && (pInputData->nFlags & OMX_BUFFERFLAG_EOS)) {
            pOutputData->nFlags |= OMX_BUFFERFLAG_EOS;
            pAacDec->hSeirenAacHandle.bSeirenSendEOS = OMX_FALSE;
            ret = OMX_ErrorNone;
            goto EXIT;
        }

        ADec_GetParams(fd, PCM_PARAM_SAMPLE_RATE, &sample_rate);
        ADec_GetParams(fd, PCM_PARAM_NUM_OF_CH, &channels);

        if (returnCodec < 0) {
            Exynos_OSAL_Log(EXYNOS_LOG_ERROR, "Seiren_ADec_GetParams failed: %d", returnCodec);
            ret = OMX_ErrorHardware;
            goto EXIT;
        }

        if (!sample_rate || !channels) {
            if (pAacDec->hSeirenAacHandle.bSeirenSendEOS == OMX_TRUE) {
                pOutputData->dataLen = 0;
                pExynosComponent->getAllDelayBuffer = OMX_TRUE;
            } else {
                pExynosComponent->getAllDelayBuffer = OMX_FALSE;
            }
            ret = OMX_ErrorNone;
            goto EXIT;//
        }

        Exynos_OSAL_Log(EXYNOS_LOG_TRACE, "numChannels(%d), samplingRate(%d)",
            channels, sample_rate);

        if (pAacDec->pcmParam.nChannels != channels ||
            pAacDec->pcmParam.nSamplingRate != sample_rate) {
            /* Change channel count and sampling rate information */
            pAacDec->pcmParam.nChannels = channels;
            pAacDec->pcmParam.nSamplingRate = sample_rate;

            /* Send Port Settings changed call back */
            (*(pExynosComponent->pCallbacks->EventHandler))
                  (pOMXComponent,
                   pExynosComponent->callbackData,
                   OMX_EventPortSettingsChanged, /* The command was completed */
                   OMX_DirOutput, /* This is the port index */
                   0,
                   NULL);
        }

        pAacDec->hSeirenAacHandle.bConfiguredSeiren = OMX_TRUE;

        if (pAacDec->hSeirenAacHandle.bSeirenSendEOS == OMX_TRUE) {
            pOutputData->dataLen = 0;
            pExynosComponent->getAllDelayBuffer = OMX_TRUE;
            ret = OMX_ErrorInputDataDecodeYet;
        } else {
            pExynosComponent->getAllDelayBuffer = OMX_FALSE;
            ret = OMX_ErrorNone;
        }
        goto EXIT;
    }

    /* Get decoded data from Seiren */
    ADec_RecvPCM(fd, &output_mem_pool);
    if (output_mem_pool.data_size > 0) {
        pOutputData->dataLen = output_mem_pool.data_size;
        Exynos_OSAL_Memcpy(pOutputData->multiPlaneBuffer.dataBuffer[AUDIO_DATA_PLANE],
                           output_mem_pool.virt_addr, output_mem_pool.data_size);
    } else {
        pOutputData->dataLen = 0;
    }

#ifdef Seiren_DUMP_TO_FILE
    if (pOutputData->dataLen > 0)
        fwrite(pOutputData->multiPlaneBuffer.dataBuffer[AUDIO_DATA_PLANE], pOutputData->dataLen, 1, outFile);
#endif

    /* Delay EOS signal until all the PCM is returned from the Seiren driver. */
    if (pAacDec->hSeirenAacHandle.bSeirenSendEOS == OMX_TRUE) {
        if (pInputData->nFlags & OMX_BUFFERFLAG_EOS) {
            returnCodec = ADec_GetParams(fd, ADEC_PARAM_GET_OUTPUT_STATUS, &isSeirenStopped);
            if (returnCodec != 0)
                Exynos_OSAL_Log(EXYNOS_LOG_ERROR, "Fail Seiren_STOP_EOS_STATE");
            if (isSeirenStopped == 1) {
                pOutputData->nFlags |= OMX_BUFFERFLAG_EOS;
                pExynosComponent->getAllDelayBuffer = OMX_FALSE;
                pAacDec->hSeirenAacHandle.bSeirenSendEOS = OMX_FALSE; /* for repeating one song */
                ret = OMX_ErrorNone;
            } else {
                pExynosComponent->getAllDelayBuffer = OMX_TRUE;
                ret = OMX_ErrorInputDataDecodeYet;
            }
        } else { /* Flush after EOS */
            pAacDec->hSeirenAacHandle.bSeirenSendEOS = OMX_FALSE;
        }
    }
EXIT:
    FunctionOut();

    return ret;
}

OMX_ERRORTYPE Exynos_Seiren_AacDec_bufferProcess(OMX_COMPONENTTYPE *pOMXComponent, EXYNOS_OMX_DATA *pInputData, EXYNOS_OMX_DATA *pOutputData)
{
    OMX_ERRORTYPE             ret = OMX_ErrorNone;
    EXYNOS_OMX_BASECOMPONENT *pExynosComponent = (EXYNOS_OMX_BASECOMPONENT *)pOMXComponent->pComponentPrivate;
    EXYNOS_OMX_BASEPORT      *pInputPort = &pExynosComponent->pExynosPort[INPUT_PORT_INDEX];
    EXYNOS_OMX_BASEPORT      *pOutputPort = &pExynosComponent->pExynosPort[OUTPUT_PORT_INDEX];

    FunctionIn();

    if ((!CHECK_PORT_ENABLED(pInputPort)) || (!CHECK_PORT_ENABLED(pOutputPort)) ||
            (!CHECK_PORT_POPULATED(pInputPort)) || (!CHECK_PORT_POPULATED(pOutputPort))) {
        if (pInputData->nFlags & OMX_BUFFERFLAG_EOS)
            ret = OMX_ErrorInputDataDecodeYet;
        else
            ret = OMX_ErrorNone;

        goto EXIT;
    }
    if (OMX_FALSE == Exynos_Check_BufferProcess_State(pExynosComponent)) {
        if (pInputData->nFlags & OMX_BUFFERFLAG_EOS)
            ret = OMX_ErrorInputDataDecodeYet;
        else
            ret = OMX_ErrorNone;

        goto EXIT;
    }

    ret = Exynos_Seiren_Aac_Decode_Block(pOMXComponent, pInputData, pOutputData);

    if (ret != OMX_ErrorNone) {
        if (ret == (OMX_ERRORTYPE)OMX_ErrorInputDataDecodeYet) {
            pOutputData->usedDataLen = 0;
            pOutputData->remainDataLen = pOutputData->dataLen;
        } else {
            pExynosComponent->pCallbacks->EventHandler((OMX_HANDLETYPE)pOMXComponent,
                                                    pExynosComponent->callbackData,
                                                    OMX_EventError, ret, 0, NULL);
        }
    } else {
        pInputData->usedDataLen += pInputData->dataLen;
        pInputData->remainDataLen = pInputData->dataLen - pInputData->usedDataLen;
        pInputData->dataLen -= pInputData->usedDataLen;
        pInputData->usedDataLen = 0;

        pOutputData->usedDataLen = 0;
        pOutputData->remainDataLen = pOutputData->dataLen;
    }

EXIT:
    FunctionOut();

    return ret;
}

OMX_ERRORTYPE Exynos_Seiren_AacDec_flushSeiren(OMX_COMPONENTTYPE *pOMXComponent, SEIREN_PORTTYPE type)
{
    OMX_ERRORTYPE                  ret = OMX_ErrorNone;
    EXYNOS_OMX_BASECOMPONENT      *pExynosComponent = (EXYNOS_OMX_BASECOMPONENT *)pOMXComponent->pComponentPrivate;
    EXYNOS_OMX_AUDIODEC_COMPONENT *pAudioDec = (EXYNOS_OMX_AUDIODEC_COMPONENT *)pExynosComponent->hComponentHandle;
    EXYNOS_AAC_HANDLE             *pAacDec = (EXYNOS_AAC_HANDLE *)pAudioDec->hCodecHandle;

    int fd = pAacDec->hSeirenAacHandle.hSeirenHandle;
    return ADec_Flush(fd, type);
}

OSCL_EXPORT_REF OMX_ERRORTYPE Exynos_OMX_ComponentInit(OMX_HANDLETYPE hComponent, OMX_STRING componentName)
{
    OMX_ERRORTYPE                  ret = OMX_ErrorNone;
    OMX_COMPONENTTYPE             *pOMXComponent = NULL;
    EXYNOS_OMX_BASECOMPONENT      *pExynosComponent = NULL;
    EXYNOS_OMX_BASEPORT           *pExynosPort = NULL;
    EXYNOS_OMX_AUDIODEC_COMPONENT *pAudioDec = NULL;
    EXYNOS_AAC_HANDLE             *pAacDec = NULL;
    audio_mem_info_t               input_mem_pool;
    audio_mem_info_t               output_mem_pool;
    OMX_S32                        fd;

    int i = 0;

    FunctionIn();

    if ((hComponent == NULL) || (componentName == NULL)) {
        Exynos_OSAL_Log(EXYNOS_LOG_ERROR, "%s: parameters are null, ret: %X", __FUNCTION__, ret);
        ret = OMX_ErrorBadParameter;
        goto EXIT;
    }
    if (Exynos_OSAL_Strcmp(EXYNOS_OMX_COMPONENT_AAC_DEC, componentName) != 0) {
        Exynos_OSAL_Log(EXYNOS_LOG_ERROR, "%s: componentName(%s) error, ret: %X", __FUNCTION__, componentName, ret);
        ret = OMX_ErrorBadParameter;
        goto EXIT;
    }

    pOMXComponent = (OMX_COMPONENTTYPE *)hComponent;
    ret = Exynos_OMX_AudioDecodeComponentInit(pOMXComponent);
    if (ret != OMX_ErrorNone) {
        Exynos_OSAL_Log(EXYNOS_LOG_ERROR, "%s: Exynos_OMX_AudioDecodeComponentInit error, ret: %X", __FUNCTION__, ret);
        goto EXIT;
    }
    pExynosComponent = (EXYNOS_OMX_BASECOMPONENT *)pOMXComponent->pComponentPrivate;
    pExynosComponent->codecType = HW_AUDIO_DEC_CODEC;

    pExynosComponent->componentName = (OMX_STRING)Exynos_OSAL_Malloc(MAX_OMX_COMPONENT_NAME_SIZE);
    if (pExynosComponent->componentName == NULL) {
        Exynos_OSAL_Log(EXYNOS_LOG_ERROR, "%s: componentName alloc error, ret: %X", __FUNCTION__, ret);
        ret = OMX_ErrorInsufficientResources;
        goto EXIT_ERROR_1;
    }
    Exynos_OSAL_Memset(pExynosComponent->componentName, 0, MAX_OMX_COMPONENT_NAME_SIZE);
    Exynos_OSAL_Strcpy(pExynosComponent->componentName, EXYNOS_OMX_COMPONENT_AAC_DEC);

    pAacDec = Exynos_OSAL_Malloc(sizeof(EXYNOS_AAC_HANDLE));
    if (pAacDec == NULL) {
        Exynos_OSAL_Log(EXYNOS_LOG_ERROR, "%s: EXYNOS_AAC_HANDLE alloc error, ret: %X", __FUNCTION__, ret);
        ret = OMX_ErrorInsufficientResources;
        goto EXIT_ERROR_2;
    }
    Exynos_OSAL_Memset(pAacDec, 0, sizeof(EXYNOS_AAC_HANDLE));
    pAudioDec = (EXYNOS_OMX_AUDIODEC_COMPONENT *)pExynosComponent->hComponentHandle;
    pAudioDec->hCodecHandle = (OMX_HANDLETYPE)pAacDec;

    /* Create and Init Seiren */
    pAacDec->hSeirenAacHandle.bSeirenLoaded = OMX_FALSE;
    fd = ADec_Create(0, ADEC_AAC, NULL);

    if (fd < 0) {
        Exynos_OSAL_Log(EXYNOS_LOG_ERROR, "Seiren_ADec_Create failed: %d", fd);
        ret = OMX_ErrorHardware;
        goto EXIT_ERROR_3;
    }
    pAacDec->hSeirenAacHandle.hSeirenHandle = fd; /* Seiren's fd */
    pAacDec->hSeirenAacHandle.bSeirenLoaded = OMX_TRUE;

    /* Get input buffer info from Seiren */
    Exynos_OSAL_Memset(&pAacDec->hSeirenAacHandle.input_mem_pool, 0, sizeof(audio_mem_info_t));
    ADec_GetIMemPoolInfo(fd, &pAacDec->hSeirenAacHandle.input_mem_pool);
    input_mem_pool = pAacDec->hSeirenAacHandle.input_mem_pool;
        
    Exynos_OSAL_Log(EXYNOS_LOG_ERROR, "eiren_Adec_GetIMemPoolInfo : %d", input_mem_pool.mem_size);

    if (input_mem_pool.virt_addr == NULL) {
        Exynos_OSAL_Log(EXYNOS_LOG_ERROR, "Seiren_Adec_GetIMemPoolInfo failed: %d", fd);
        ret = OMX_ErrorHardware;
        goto EXIT_ERROR_5;
    }

    pExynosPort = &pExynosComponent->pExynosPort[INPUT_PORT_INDEX];
    pExynosPort->processData.allocSize = input_mem_pool.mem_size;
    pExynosPort->processData.multiPlaneBuffer.dataBuffer[AUDIO_DATA_PLANE] = input_mem_pool.virt_addr;

    /* Get output buffer info from Seiren */
    Exynos_OSAL_Memset(&pAacDec->hSeirenAacHandle.output_mem_pool, 0, sizeof(audio_mem_info_t));
    ADec_GetOMemPoolInfo(fd, &pAacDec->hSeirenAacHandle.output_mem_pool);
    output_mem_pool = pAacDec->hSeirenAacHandle.output_mem_pool;
    if (output_mem_pool.virt_addr == NULL) {
        Exynos_OSAL_Log(EXYNOS_LOG_ERROR, "Seiren_ADec_GetOMemPoolInfo failed: %d", fd);
        ret = OMX_ErrorHardware;
        goto EXIT_ERROR_6;
    }

    /* Set componentVersion */
    pExynosComponent->componentVersion.s.nVersionMajor = VERSIONMAJOR_NUMBER;
    pExynosComponent->componentVersion.s.nVersionMinor = VERSIONMINOR_NUMBER;
    pExynosComponent->componentVersion.s.nRevision     = REVISION_NUMBER;
    pExynosComponent->componentVersion.s.nStep         = STEP_NUMBER;

    /* Set specVersion */
    pExynosComponent->specVersion.s.nVersionMajor = VERSIONMAJOR_NUMBER;
    pExynosComponent->specVersion.s.nVersionMinor = VERSIONMINOR_NUMBER;
    pExynosComponent->specVersion.s.nRevision     = REVISION_NUMBER;
    pExynosComponent->specVersion.s.nStep         = STEP_NUMBER;

    /* Input port */
    pExynosPort = &pExynosComponent->pExynosPort[INPUT_PORT_INDEX];
    pExynosPort->portDefinition.nBufferCountActual = input_mem_pool.block_count;
    pExynosPort->portDefinition.nBufferCountMin = input_mem_pool.block_count;
    pExynosPort->portDefinition.nBufferSize = input_mem_pool.mem_size;
    pExynosPort->portDefinition.bEnabled = OMX_TRUE;
    Exynos_OSAL_Memset(pExynosPort->portDefinition.format.audio.cMIMEType, 0, MAX_OMX_MIMETYPE_SIZE);
    Exynos_OSAL_Strcpy(pExynosPort->portDefinition.format.audio.cMIMEType, "audio/aac");
    pExynosPort->portDefinition.format.audio.pNativeRender = 0;
    pExynosPort->portDefinition.format.audio.bFlagErrorConcealment = OMX_FALSE;
    pExynosPort->portDefinition.format.audio.eEncoding = OMX_AUDIO_CodingAAC;
    pExynosPort->portWayType = WAY1_PORT;

    /* Output port */
    pExynosPort = &pExynosComponent->pExynosPort[OUTPUT_PORT_INDEX];
    pExynosPort->portDefinition.nBufferCountActual = output_mem_pool.block_count;
    pExynosPort->portDefinition.nBufferCountMin = output_mem_pool.block_count;
    pExynosPort->portDefinition.nBufferSize = output_mem_pool.mem_size;
    pExynosPort->portDefinition.bEnabled = OMX_TRUE;
    Exynos_OSAL_Memset(pExynosPort->portDefinition.format.audio.cMIMEType, 0, MAX_OMX_MIMETYPE_SIZE);
    Exynos_OSAL_Strcpy(pExynosPort->portDefinition.format.audio.cMIMEType, "audio/raw");
    pExynosPort->portDefinition.format.audio.pNativeRender = 0;
    pExynosPort->portDefinition.format.audio.bFlagErrorConcealment = OMX_FALSE;
    pExynosPort->portDefinition.format.audio.eEncoding = OMX_AUDIO_CodingPCM;
    pExynosPort->portWayType = WAY1_PORT;

    /* Default values for Aac audio param */
    INIT_SET_SIZE_VERSION(&pAacDec->aacParam, OMX_AUDIO_PARAM_AACPROFILETYPE);
    pAacDec->aacParam.nPortIndex       = INPUT_PORT_INDEX;
    pAacDec->aacParam.nChannels        = DEFAULT_AUDIO_CHANNELS_NUM;
    pAacDec->aacParam.nBitRate         = 0;
    pAacDec->aacParam.nSampleRate      = DEFAULT_AUDIO_SAMPLING_FREQ;
    pAacDec->aacParam.nAudioBandWidth  = 0;
    pAacDec->aacParam.eChannelMode     = OMX_AUDIO_ChannelModeStereo;
    pAacDec->aacParam.eAACProfile      = OMX_AUDIO_AACObjectNull;
    pAacDec->aacParam.eAACStreamFormat = OMX_AUDIO_AACStreamFormatMP2ADTS;

    /* Default values for PCM audio param */
    INIT_SET_SIZE_VERSION(&pAacDec->pcmParam, OMX_AUDIO_PARAM_PCMMODETYPE);
    pAacDec->pcmParam.nPortIndex         = OUTPUT_PORT_INDEX;
    pAacDec->pcmParam.nChannels          = DEFAULT_AUDIO_CHANNELS_NUM;
    pAacDec->pcmParam.eNumData           = OMX_NumericalDataSigned;
    pAacDec->pcmParam.eEndian            = OMX_EndianLittle;
    pAacDec->pcmParam.bInterleaved       = OMX_TRUE;
    pAacDec->pcmParam.nBitPerSample      = DEFAULT_AUDIO_BIT_PER_SAMPLE;
    pAacDec->pcmParam.nSamplingRate      = DEFAULT_AUDIO_SAMPLING_FREQ;
    pAacDec->pcmParam.ePCMMode           = OMX_AUDIO_PCMModeLinear;
    pAacDec->pcmParam.eChannelMapping[0] = OMX_AUDIO_ChannelLF;
    pAacDec->pcmParam.eChannelMapping[1] = OMX_AUDIO_ChannelRF;

    pOMXComponent->GetParameter      = &Exynos_Seiren_AacDec_GetParameter;
    pOMXComponent->SetParameter      = &Exynos_Seiren_AacDec_SetParameter;
    pOMXComponent->GetConfig         = &Exynos_Seiren_AacDec_GetConfig;
    pOMXComponent->SetConfig         = &Exynos_Seiren_AacDec_SetConfig;
    pOMXComponent->GetExtensionIndex = &Exynos_Seiren_AacDec_GetExtensionIndex;
    pOMXComponent->ComponentRoleEnum = &Exynos_Seiren_AacDec_ComponentRoleEnum;
    pOMXComponent->ComponentDeInit   = &Exynos_OMX_ComponentDeinit;

    /* ToDo: Change the function name associated with a specific codec */
    pExynosComponent->exynos_codec_componentInit      = &Exynos_Seiren_AacDec_Init;
    pExynosComponent->exynos_codec_componentTerminate = &Exynos_Seiren_AacDec_Terminate;
    pAudioDec->exynos_codec_bufferProcess = &Exynos_Seiren_AacDec_bufferProcess;
    pAudioDec->exynos_codec_flushSeiren = &Exynos_Seiren_AacDec_flushSeiren;
    pAudioDec->exynos_checkInputFrame = NULL;

    pExynosComponent->currentState = OMX_StateLoaded;

    ret = OMX_ErrorNone;
    goto EXIT; /* This function is performed successfully. */

EXIT_ERROR_6:
    pExynosPort = &pExynosComponent->pExynosPort[INPUT_PORT_INDEX];
    pExynosPort->processData.multiPlaneBuffer.dataBuffer[AUDIO_DATA_PLANE] = NULL;
    pExynosPort->processData.allocSize = 0;
EXIT_ERROR_5:
EXIT_ERROR_4:
    ADec_Destroy(pAacDec->hSeirenAacHandle.hSeirenHandle);
EXIT_ERROR_3:
    Exynos_OSAL_Free(pAacDec);
    pAudioDec->hCodecHandle = NULL;
EXIT_ERROR_2:
    Exynos_OSAL_Free(pExynosComponent->componentName);
    pExynosComponent->componentName = NULL;
EXIT_ERROR_1:
    Exynos_OMX_AudioDecodeComponentDeinit(pOMXComponent);
EXIT:
    FunctionOut();

    return ret;
}

OMX_ERRORTYPE Exynos_OMX_ComponentDeinit(OMX_HANDLETYPE hComponent)
{
    OMX_ERRORTYPE             ret = OMX_ErrorNone;
    OMX_COMPONENTTYPE        *pOMXComponent = NULL;
    EXYNOS_OMX_BASECOMPONENT *pExynosComponent = NULL;
    EXYNOS_AAC_HANDLE        *pAacDec = NULL;
    EXYNOS_OMX_BASEPORT      *pExynosPort = NULL;

    FunctionIn();

    if (hComponent == NULL) {
        ret = OMX_ErrorBadParameter;
        goto EXIT;
    }
    pOMXComponent = (OMX_COMPONENTTYPE *)hComponent;
    pExynosComponent = (EXYNOS_OMX_BASECOMPONENT *)pOMXComponent->pComponentPrivate;

    Exynos_OSAL_Free(pExynosComponent->componentName);
    pExynosComponent->componentName = NULL;

    pAacDec = (EXYNOS_AAC_HANDLE *)((EXYNOS_OMX_AUDIODEC_COMPONENT *)pExynosComponent->hComponentHandle)->hCodecHandle;
    if (pAacDec != NULL) {
        if (pAacDec->hSeirenAacHandle.bSeirenLoaded == OMX_TRUE) {
            ADec_Destroy(pAacDec->hSeirenAacHandle.hSeirenHandle);
        }
        Exynos_OSAL_Free(pAacDec);
        ((EXYNOS_OMX_AUDIODEC_COMPONENT *)pExynosComponent->hComponentHandle)->hCodecHandle = NULL;
    }

    ret = Exynos_OMX_AudioDecodeComponentDeinit(pOMXComponent);
    if (ret != OMX_ErrorNone) {
        goto EXIT;
    }

    ret = OMX_ErrorNone;

EXIT:
    FunctionOut();

    return ret;
}
