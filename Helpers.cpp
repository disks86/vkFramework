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

#include "Helpers.h"

VKAPI_ATTR VkBool32 VKAPI_CALL DebugReportCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char* layerPrefix, const char* message, void* userData)
{
    switch (flags)
    {
        case VK_DEBUG_REPORT_INFORMATION_BIT_EXT:
            Log(info) << "------DebugReport(Info)------" << std::endl;
            Log(info) << "ObjectType: " << objectType << std::endl;
            Log(info) << "Object: " << object << std::endl;
            Log(info) << "Location: " << location << std::endl;
            Log(info) << "MessageCode: " << messageCode << std::endl;
            Log(info) << "LayerPrefix: " << layerPrefix << std::endl;
            Log(info) << "Message: " << message << std::endl;
            Log(info) << "-----------------------------" << std::endl;
            break;
        case VK_DEBUG_REPORT_WARNING_BIT_EXT:
            Log(warning) << "------DebugReport(Warn)------" << std::endl;
            Log(warning) << "ObjectType: " << objectType << std::endl;
            Log(warning) << "Object: " << object << std::endl;
            Log(warning) << "Location: " << location << std::endl;
            Log(warning) << "MessageCode: " << messageCode << std::endl;
            Log(warning) << "LayerPrefix: " << layerPrefix << std::endl;
            Log(warning) << "Message: " << message << std::endl;
            Log(warning) << "-----------------------------" << std::endl;
            break;
        case VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT:
            Log(warning) << "------DebugReport(Perf)------" << std::endl;
            Log(warning) << "ObjectType: " << objectType << std::endl;
            Log(warning) << "Object: " << object << std::endl;
            Log(warning) << "Location: " << location << std::endl;
            Log(warning) << "MessageCode: " << messageCode << std::endl;
            Log(warning) << "LayerPrefix: " << layerPrefix << std::endl;
            Log(warning) << "Message: " << message << std::endl;
            Log(warning) << "-----------------------------" << std::endl;
            break;
        case VK_DEBUG_REPORT_ERROR_BIT_EXT:
            Log(error) << "------DebugReport(Error)------" << std::endl;
            Log(error) << "ObjectType: " << objectType << std::endl;
            Log(error) << "Object: " << object << std::endl;
            Log(error) << "Location: " << location << std::endl;
            Log(error) << "MessageCode: " << messageCode << std::endl;
            Log(error) << "LayerPrefix: " << layerPrefix << std::endl;
            Log(error) << "Message: " << message << std::endl;
            Log(error) << "------------------------------" << std::endl;
            break;
        case VK_DEBUG_REPORT_DEBUG_BIT_EXT:
            Log(warning) << "------DebugReport(Debug)------" << std::endl;
            Log(warning) << "ObjectType: " << objectType << std::endl;
            Log(warning) << "Object: " << object << std::endl;
            Log(warning) << "Location: " << location << std::endl;
            Log(warning) << "MessageCode: " << messageCode << std::endl;
            Log(warning) << "LayerPrefix: " << layerPrefix << std::endl;
            Log(warning) << "Message: " << message << std::endl;
            Log(warning) << "------------------------------" << std::endl;
            break;
        default:
            Log(error) << "------DebugReport(?)------" << std::endl;
            Log(error) << "ObjectType: " << objectType << std::endl;
            Log(error) << "Object: " << object << std::endl;
            Log(error) << "Location: " << location << std::endl;
            Log(error) << "MessageCode: " << messageCode << std::endl;
            Log(error) << "LayerPrefix: " << layerPrefix << std::endl;
            Log(error) << "Message: " << message << std::endl;
            Log(error) << "--------------------------" << std::endl;
            break;
    }

    return VK_FALSE;
}

VKAPI_ATTR void VKAPI_CALL vkCmdPushDescriptorSetKHR(
        VkCommandBuffer                             commandBuffer,
        VkPipelineBindPoint                         pipelineBindPoint,
        VkPipelineLayout                            layout,
        uint32_t                                    set,
        uint32_t                                    descriptorWriteCount,
        const VkWriteDescriptorSet*                 pDescriptorWrites)
{
    if (pfn_vkCmdPushDescriptorSetKHR == nullptr)
    {
        return;
    }

    pfn_vkCmdPushDescriptorSetKHR(
            commandBuffer,
            pipelineBindPoint,
            layout,
            set,
            descriptorWriteCount,
            pDescriptorWrites
    );
}

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugReportCallbackEXT(
        VkInstance                                  instance,
        const VkDebugReportCallbackCreateInfoEXT*   pCreateInfo,
        const VkAllocationCallbacks*                pAllocator,
        VkDebugReportCallbackEXT*                   pCallback)
{
    if (pfn_vkCreateDebugReportCallbackEXT == nullptr)
    {
        return VK_NOT_READY;
    }

    return pfn_vkCreateDebugReportCallbackEXT(
            instance,
            pCreateInfo,
            pAllocator,
            pCallback
    );
}

VKAPI_ATTR void VKAPI_CALL vkDestroyDebugReportCallbackEXT(
        VkInstance                                  instance,
        VkDebugReportCallbackEXT                    callback,
        const VkAllocationCallbacks*                pAllocator)
{
    if (pfn_vkDestroyDebugReportCallbackEXT == nullptr)
    {
        return;
    }

    pfn_vkDestroyDebugReportCallbackEXT(
            instance,
            callback,
            pAllocator
    );
}

VKAPI_ATTR void VKAPI_CALL vkDebugReportMessageEXT(
        VkInstance                                  instance,
        VkDebugReportFlagsEXT                       flags,
        VkDebugReportObjectTypeEXT                  objectType,
        uint64_t                                    object,
        size_t                                      location,
        int32_t                                     messageCode,
        const char*                                 pLayerPrefix,
        const char*                                 pMessage)
{
    if (pfn_vkDebugReportMessageEXT == nullptr)
    {
        return;
    }

    pfn_vkDebugReportMessageEXT(
            instance,
            flags,
            objectType,
            object,
            location,
            messageCode,
            pLayerPrefix,
            pMessage
    );
}

uint64_t MakeId(const std::string& arr)
{
    uint64_t output = 0;
    for (size_t i = 0; i < std::min(arr.size(),(size_t)8); i++)
    {
        output |= arr[i] << (i * 8);
    }
    return output;
}