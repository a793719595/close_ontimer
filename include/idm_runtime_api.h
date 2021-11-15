/****************************************************************************
 *
 * Copyright 2020 XiaoMi All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/
#ifndef RUNTIME_INCLUDE_IDM_RUNTIME_API_H_
#define RUNTIME_INCLUDE_IDM_RUNTIME_API_H_

// XIAOMI IOT IDM runtime service
// SAMPLE:
//  idmrt_start();
//  ....[DO YOUR WORK]....
/// idmrt_stop();

// [CHANGE LOGS]:
// 1. date: 2020-5, v:0.0.1, desp: the frist demo version


#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
  /* Windows - set up dll import/export decorators. */
# if defined(IDM_RUNTIME_EXPORT)
    /* Building shared library. */
#   define IDM_RUNTIME_API __declspec(dllexport)
# else
    /* Using shared library. */
#   define IDM_RUNTIME_API __declspec(dllimport)
# endif
#elif __GNUC__ >= 4
# define IDM_RUNTIME_API __attribute__((visibility("default")))
#else
# define IDM_RUNTIME_API /* nothing */
#endif

#include <stdlib.h>

/**
 * \brief          get version number
 *
 * \return        version number
 */
IDM_RUNTIME_API const char* idmrt_version();

/**
 * @brief idmrt_crash_reports_cb
 * @param minidump_file_name: the minidump file name
 */
typedef void (*idmrt_crash_reports_cb)(void*context, const char* minidump_file_name);

/**
 * @brief       enable or disable crash dumps.(should just call once)
 *              example:
 *                #define crash_svr_url = "http://10.221.65.123:1127/crashreports"
 *                idmrt_enable_crash_reporter(nullptr, nullptr, crash_svr_url);
 *
 * @param cb : callback that will be invokded when crashes
 * @param context: callback's context
 * @param crash_reports_url: the breakpad server url
 * @return
 */
IDM_RUNTIME_API void idmrt_enable_crash_reporter(
   idmrt_crash_reports_cb cb,
   void* context,
   const char* crash_reports_url
   );

/**
 * \brief          Start the idm runtime. should call just once
 *
 * \return        \c 0 success
 * \return        \c !0 error
 */
IDM_RUNTIME_API int idmrt_start();

/**
 * \brief           Stop the IDM Runtime.
 *
 * \return        \c 0 success
 * \return        \c !0 error
 */
IDM_RUNTIME_API int idmrt_stop();

/**
 * \brief           Check the IDM Runtime is running or not.
 *
 * \return        \c 1 stated
 * \return        \c 0 not started
 */
IDM_RUNTIME_API int idmrt_is_started();

/**
 * @brief log level
 */
typedef enum {
  IDMRT_LOG_LVL_ERROR = 1,
  IDMRT_LOG_LVL_WARN,
  IDMRT_LOG_LVL_INFO,
  IDMRT_LOG_LVL_DEBUG,
} idmrt_log_level_t;
/**
 * \brief           set log file path, if not set it will be auto output.
 *
 * \param log_file_path   The file that log will be ouput.[encoded in utf8]
 * \param level   The log level.
 * \return
 */
IDM_RUNTIME_API void idmrt_set_logger(const char* log_file_path, idmrt_log_level_t level);

/**
 * \brief           set logger hook when output
 *
 * \param hook      callback function.[msg is encoded in utf8]
 * \return
 */
IDM_RUNTIME_API void idmrt_set_logger_hook(void (*hook)(const char* utf8_log, size_t size));

/**
 * \brief          Start stats OneTrackService by idm runtime sdk.
 *
 * \return        \c 0 success
 * \return        \c !0 error
 */
IDM_RUNTIME_API int idmrt_start_onetrack_service();

#ifdef __cplusplus
}
#endif

#endif  // RUNTIME_INCLUDE_IDM_RUNTIME_API_H_
