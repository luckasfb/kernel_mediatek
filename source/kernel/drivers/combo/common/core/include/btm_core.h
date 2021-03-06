/*! \file
    \brief  Declaration of library functions

    Any definitions in this file will be shared among GLUE Layer and internal Driver Stack.
*/

/*******************************************************************************
* Copyright (c) 2009 MediaTek Inc.
*
* All rights reserved. Copying, compilation, modification, distribution
* or any other use whatsoever of this material is strictly prohibited
* except in accordance with a Software License Agreement with
* MediaTek Inc.
********************************************************************************
*/

/*******************************************************************************
* LEGAL DISCLAIMER
*
* BY OPENING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND
* AGREES THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK
* SOFTWARE") RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE
* PROVIDED TO BUYER ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY
* DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT
* LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE
* ANY WARRANTY WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY
* WHICH MAY BE USED BY, INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK
* SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY
* WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE
* FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION OR TO
* CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
* BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE
* LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL
* BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT
* ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY
* BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
*
* THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE
* WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT
* OF LAWS PRINCIPLES.  ANY DISPUTES, CONTROVERSIES OR CLAIMS ARISING
* THEREOF AND RELATED THERETO SHALL BE SETTLED BY ARBITRATION IN SAN
* FRANCISCO, CA, UNDER THE RULES OF THE INTERNATIONAL CHAMBER OF COMMERCE
* (ICC).
********************************************************************************
*/

#ifndef _BTM_CORE_H
#define _BTM_CORE_H

#include "osal_typedef.h"
#include "osal.h"
#include "stp_wmt.h"

/*******************************************************************************
*                         C O M P I L E R   F L A G S
********************************************************************************
*/

/*******************************************************************************
*                                 M A C R O S
********************************************************************************
*/
#define STP_BTM_OPERATION_FAIL    (-1)
#define STP_BTM_OPERATION_SUCCESS (0) 

#define STP_BTM_OP_BUF_SIZE (64)

#define BTM_THREAD_NAME "mtk_stp_btm"
/*******************************************************************************
*                    E X T E R N A L   R E F E R E N C E S
********************************************************************************
*/



/*******************************************************************************
*                              C O N S T A N T S
********************************************************************************
*/

/*******************************************************************************
*                             D A T A   T Y P E S
********************************************************************************
*/
typedef enum _ENUM_STP_BTM_OPID_T {
    STP_OPID_BTM_RETRY = 0x0,
    STP_OPID_BTM_RST = 0x1,
    STP_OPID_BTM_DBG_DUMP = 0x2,
    STP_OPID_BTM_EXIT,
    STP_OPID_BTM_NUM
} ENUM_STP_BTM_OPID_T, *P_ENUM_STP_BTM_OPID_T;

typedef OSAL_OP_DAT STP_BTM_OP;
typedef P_OSAL_OP_DAT P_STP_BTM_OP;

typedef struct mtk_stp_btm
{
    OSAL_THREAD           BTMd;   /* main thread (wmtd) handle */
    OSAL_EVENT            STPd_event;
    OSAL_UNSLEEPABLE_LOCK wq_spinlock;

    OSAL_OP_Q    rFreeOpQ; /* free op queue */
    OSAL_OP_Q    rActiveOpQ; /* active op queue */
    OSAL_OP      arQue[STP_BTM_OP_BUF_SIZE]; /* real op instances */
    
    /*wmt_notify*/
    INT32 (*wmt_notify)(MTKSTP_BTM_WMT_OP_T);
}MTKSTP_BTM_T;


/*******************************************************************************
*                            P U B L I C   D A T A
********************************************************************************
*/

/*******************************************************************************
*                           P R I V A T E   D A T A
********************************************************************************
*/


/*******************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
********************************************************************************
*/

INT32 stp_btm_notify_wmt_rst_wq(MTKSTP_BTM_T *stp_btm);
INT32 stp_btm_notify_stp_retry_wq(MTKSTP_BTM_T *stp_btm);
INT32 stp_btm_notify_wmt_dmp_wq(MTKSTP_BTM_T *stp_btm);
INT32 stp_btm_deinit(MTKSTP_BTM_T *stp_btm);
INT32 stp_btm_reset_btm_wq(MTKSTP_BTM_T *stp_btm);


MTKSTP_BTM_T *stp_btm_init(void);

/*******************************************************************************
*                              F U N C T I O N S
********************************************************************************
*/

#endif
