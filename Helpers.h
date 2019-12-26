/*
 * MIT License
 *
 * Copyright (c) 2019 Christopher Joseph Dean Schaefer
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef VKFRAMEWORK_HELPERS_H
#define VKFRAMEWORK_HELPERS_H

#include <cstdint>
#include <cstddef>
#include <string_view>
#include <string>
#include <locale>
#include <vector>

#include <vulkan/vulkan.hpp>
#include <vulkan/vk_sdk_platform.h>

#include "LogManager.h"

#if defined _WIN32 || defined __CYGWIN__
#ifdef MAKEDLL
    #ifdef __GNUC__
      #define EXPORTED __attribute__ ((dllexport))
    #else
      #define EXPORTED __declspec(dllexport)
    #endif
  #else
    #ifdef __GNUC__
      #define EXPORTED __attribute__ ((dllimport))
    #else
      #define EXPORTED __declspec(dllimport)
    #endif
  #endif
  #define NOT_EXPORTED
#else
#if __GNUC__ >= 4
    #define EXPORTED __attribute__ ((visibility ("default")))
    #define NOT_EXPORTED  __attribute__ ((visibility ("hidden")))
#else
    #define EXPORTED
    #define NOT_EXPORTED
#endif
#endif

#ifndef VEC3_SIZE
#define VEC3_SIZE (sizeof(float)*3)
#endif // !VEC3_SIZE

#ifndef VEC4_SIZE
#define VEC4_SIZE (sizeof(float)*4)
#endif // !VEC4_SIZE

VKAPI_ATTR VkBool32 VKAPI_CALL DebugReportCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* layerPrefix, const char* message, void* userData);

static PFN_vkCmdPushDescriptorSetKHR pfn_vkCmdPushDescriptorSetKHR;
VKAPI_ATTR void VKAPI_CALL vkCmdPushDescriptorSetKHR(
        VkCommandBuffer                             commandBuffer,
VkPipelineBindPoint                         pipelineBindPoint,
        VkPipelineLayout                            layout,
uint32_t                                    set,
        uint32_t                                    descriptorWriteCount,
const VkWriteDescriptorSet*                 pDescriptorWrites);

static PFN_vkCreateDebugReportCallbackEXT pfn_vkCreateDebugReportCallbackEXT;
VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugReportCallbackEXT(
        VkInstance                                  instance,
        const VkDebugReportCallbackCreateInfoEXT*   pCreateInfo,
        const VkAllocationCallbacks*                pAllocator,
        VkDebugReportCallbackEXT*                   pCallback);

static PFN_vkDestroyDebugReportCallbackEXT pfn_vkDestroyDebugReportCallbackEXT;
VKAPI_ATTR void VKAPI_CALL vkDestroyDebugReportCallbackEXT(
        VkInstance                                  instance,
VkDebugReportCallbackEXT                    callback,
const VkAllocationCallbacks*                pAllocator);

static PFN_vkDebugReportMessageEXT pfn_vkDebugReportMessageEXT;
VKAPI_ATTR void VKAPI_CALL vkDebugReportMessageEXT(
        VkInstance                                  instance,
VkDebugReportFlagsEXT                       flags,
        VkDebugReportObjectTypeEXT                  objectType,
uint64_t                                    object,
        size_t                                      location,
int32_t                                     messageCode,
const char*                                 pLayerPrefix,
const char*                                 pMessage);

uint64_t MakeId(const std::string& arr);

template<size_t N>
constexpr uint64_t MakeId(const char(&arr)[N])
{
    static_assert(N <= 8, "Identifier string too long!");

    uint64_t output = 0;
    for (size_t i = 0; i < N; i++)
    {
        output |= arr[i] << (i * 8);
    }
    return output;
}

static inline void LTrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch)
    {
        std::locale loc;
        return !std::isspace(ch, loc);
    }));
}

static inline void RTrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch)
    {
        std::locale loc;
        return !std::isspace(ch, loc);
    }).base(), s.end());
}

static inline void Trim(std::string &s)
{
    LTrim(s);
    RTrim(s);
}

#endif //VKFRAMEWORK_HELPERS_H
