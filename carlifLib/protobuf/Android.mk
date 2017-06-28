
# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
#

LOCAL_PATH := $(call my-dir)

CC_LITE_SRC_FILES := \
	src/google/protobuf/stubs/atomicops_internals_x86_gcc.cc	\
	src/google/protobuf/stubs/atomicops_internals_x86_msvc.cc	\
	src/google/protobuf/stubs/common.cc	\
	src/google/protobuf/stubs/once.cc	\
	src/google/protobuf/stubs/stringprintf.cc	\
	src/google/protobuf/extension_set.cc	\
	src/google/protobuf/generated_message_util.cc	\
	src/google/protobuf/message_lite.cc	\
	src/google/protobuf/repeated_field.cc	\
	src/google/protobuf/wire_format_lite.cc	\
	src/google/protobuf/io/coded_stream.cc	\
	src/google/protobuf/io/zero_copy_stream.cc	\
	src/google/protobuf/io/zero_copy_stream_impl_lite.cc	\

CC_PROTOC_SRC_FILES :=	\
	src/google/protobuf/compiler/code_generator.cc	\
	src/google/protobuf/compiler/command_line_interface.cc	\
	src/google/protobuf/compiler/plugin.cc	\
	src/google/protobuf/compiler/plugin.pb.cc	\
	src/google/protobuf/compiler/subprocess.cc	\
	src/google/protobuf/compiler/zip_writer.cc	\
	src/google/protobuf/compiler/cpp/cpp_enum.cc	\
	src/google/protobuf/compiler/cpp/cpp_enum_field.cc	\
	src/google/protobuf/compiler/cpp/cpp_extension.cc	\
	src/google/protobuf/compiler/cpp/cpp_field.cc	\
	src/google/protobuf/compiler/cpp/cpp_file.cc	\
	src/google/protobuf/compiler/cpp/cpp_generator.cc	\
	src/google/protobuf/compiler/cpp/cpp_helpers.cc	\
	src/google/protobuf/compiler/cpp/cpp_message.cc	\
	src/google/protobuf/compiler/cpp/cpp_message_field.cc	\
	src/google/protobuf/compiler/cpp/cpp_primitive_field.cc	\
	src/google/protobuf/compiler/cpp/cpp_service.cc	\
	src/google/protobuf/compiler/cpp/cpp_string_field.cc 

CC_ANDROID_PROTOC_SRC_FILES :=	\
	$(LOCAL_PATH)/src/google/protobuf/compiler/main.cc


CC_MAIN_SRC_FILES := \
	$(LOCAL_PATH)/src/main.cc	\
	$(LOCAL_PATH)/src/Message.pb.cc	\
	$(LOCAL_PATH)/src/Message1.pb.cc

CC_MAIN_INCLUDES := \
	$(LOCAL_PATH)/src/src	\
	$(LOCAL_PATH)/android \
	$(LOCAL_PATH)/src

# C++ lite library
# =======================================================
include $(CLEAR_VARS)
LOCAL_MODULE := libprotobuf-lite
LOCAL_MODULE_TAGS := optional
LOCAL_CPP_EXTENSION := .cc
LOCAL_SRC_FILES := $(CC_LITE_SRC_FILES)
LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/android \
    $(LOCAL_PATH)/src
LOCAL_SHARED_LIBRARIES := libcutils libutils
LOCAL_CFLAGS := -DGOOGLE_PROTOBUF_NO_RTTI
LOCAL_SDK_VERSION := 8
LOCAL_NDK_STL_VARIANT := stlport_static
include $(BUILD_STATIC_LIBRARY)


# C++ protoc library
# =======================================================
include $(CLEAR_VARS)
LOCAL_MODULE := libprotoc
LOCAL_CPP_EXTENSION := .cc
LOCAL_SRC_FILES := $(CC_PROTOC_SRC_FILES)
LOCAL_EXPORT_C_INCLUDES := \
    $(LOCAL_PATH)/android \
    $(LOCAL_PATH)/src
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/android \
    $(LOCAL_PATH)/src
LOCAL_STATIC_LIBRARIES := libprotobuf
LOCAL_CFLAGS := -DGOOGLE_PROTOBUF_NO_RTTI
LOCAL_SDK_VERSION := 8
LOCAL_NDK_STL_VARIANT := stlport_static
include $(BUILD_STATIC_LIBRARY)


# C++ full library
# =======================================================
include $(CLEAR_VARS)
LOCAL_MODULE := libprotobuf
LOCAL_CPP_EXTENSION := .cc
LOCAL_SRC_FILES := \
	src/google/protobuf/stubs/atomicops_internals_x86_gcc.cc	\
	src/google/protobuf/stubs/atomicops_internals_x86_msvc.cc	\
	src/google/protobuf/stubs/common.cc	\
	src/google/protobuf/stubs/once.cc	\
	src/google/protobuf/stubs/stringprintf.cc	\
	src/google/protobuf/extension_set.cc	\
	src/google/protobuf/generated_message_util.cc	\
	src/google/protobuf/message_lite.cc	\
	src/google/protobuf/repeated_field.cc	\
	src/google/protobuf/wire_format_lite.cc	\
	src/google/protobuf/io/coded_stream.cc	\
	src/google/protobuf/io/zero_copy_stream.cc	\
	src/google/protobuf/io/zero_copy_stream_impl_lite.cc	\
	src/google/protobuf/stubs/strutil.cc	\
	src/google/protobuf/stubs/substitute.cc	\
	src/google/protobuf/stubs/structurally_valid.cc	\
	src/google/protobuf/descriptor.cc	\
	src/google/protobuf/descriptor.pb.cc	\
	src/google/protobuf/descriptor_database.cc	\
	src/google/protobuf/dynamic_message.cc	\
	src/google/protobuf/extension_set_heavy.cc	\
	src/google/protobuf/generated_message_reflection.cc	\
	src/google/protobuf/message.cc	\
	src/google/protobuf/reflection_ops.cc	\
	src/google/protobuf/service.cc	\
	src/google/protobuf/text_format.cc	\
	src/google/protobuf/unknown_field_set.cc	\
	src/google/protobuf/wire_format.cc	\
	src/google/protobuf/io/gzip_stream.cc	\
	src/google/protobuf/io/printer.cc	\
	src/google/protobuf/io/tokenizer.cc	\
	src/google/protobuf/io/zero_copy_stream_impl.cc	\
	src/google/protobuf/compiler/importer.cc	\
	src/google/protobuf/compiler/parser.cc
LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/android \
    $(LOCAL_PATH)/src
LOCAL_EXPORT_C_INCLUDES := \
    $(LOCAL_PATH)/android \
    $(LOCAL_PATH)/src
LOCAL_CFLAGS := -DGOOGLE_PROTOBUF_NO_RTTI
LOCAL_EXPORT_CFLAGS := -DGOOGLE_PROTOBUF_NO_RTTI
LOCAL_SDK_VERSION := 8
LOCAL_NDK_STL_VARIANT := stlport_static
include $(BUILD_STATIC_LIBRARY)


# main execute 
# =======================================================
#include $(CLEAR_VARS)
#LOCAL_MODULE := main
#LOCAL_CFLAGS := -DGOOGLE_PROTOBUF_NO_RTTI
#LOCAL_C_INCLUDES := $(CC_MAIN_INCLUDES)
#LOCAL_SRC_FILES += $(CC_MAIN_SRC_FILES)
#LOCAL_STATIC_LIBRARIES := libprotobuf
#LOCAL_STATIC_LIBRARIES += libprotoc
#include $(BUILD_EXECUTABLE)  

# protoc execute 
# =======================================================
include $(CLEAR_VARS)
LOCAL_MODULE := androidProtoc
LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/android \
    $(LOCAL_PATH)/src
LOCAL_EXPORT_C_INCLUDES := \
    $(LOCAL_PATH)/android \
    $(LOCAL_PATH)/src
#LOCAL_SRC_FILES := $(CC_ANDROID_PROTOC_SRC_FILES)
LOCAL_SRC_FILES += \
	src/google/protobuf/stubs/atomicops_internals_x86_gcc.cc	\
	src/google/protobuf/stubs/atomicops_internals_x86_msvc.cc	\
	src/google/protobuf/stubs/common.cc	\
	src/google/protobuf/stubs/once.cc	\
	src/google/protobuf/stubs/stringprintf.cc	\
	src/google/protobuf/extension_set.cc	\
	src/google/protobuf/generated_message_util.cc	\
	src/google/protobuf/message_lite.cc	\
	src/google/protobuf/repeated_field.cc	\
	src/google/protobuf/wire_format_lite.cc	\
	src/google/protobuf/io/coded_stream.cc	\
	src/google/protobuf/io/zero_copy_stream.cc	\
	src/google/protobuf/io/zero_copy_stream_impl_lite.cc	\
	src/google/protobuf/stubs/strutil.cc	\
	src/google/protobuf/stubs/substitute.cc	\
	src/google/protobuf/stubs/structurally_valid.cc	\
	src/google/protobuf/descriptor.cc	\
	src/google/protobuf/descriptor.pb.cc	\
	src/google/protobuf/descriptor_database.cc	\
	src/google/protobuf/dynamic_message.cc	\
	src/google/protobuf/extension_set_heavy.cc	\
	src/google/protobuf/generated_message_reflection.cc	\
	src/google/protobuf/message.cc	\
	src/google/protobuf/reflection_ops.cc	\
	src/google/protobuf/service.cc	\
	src/google/protobuf/text_format.cc	\
	src/google/protobuf/unknown_field_set.cc	\
	src/google/protobuf/wire_format.cc	\
	src/google/protobuf/io/gzip_stream.cc	\
	src/google/protobuf/io/printer.cc	\
	src/google/protobuf/io/tokenizer.cc	\
	src/google/protobuf/io/zero_copy_stream_impl.cc	\
	src/google/protobuf/compiler/importer.cc	\
	src/google/protobuf/compiler/parser.cc	\
	src/google/protobuf/compiler/main.cc

LOCAL_CPP_EXTENSION += .cc
LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS += -Wno-error=non-virtual-dtor
LOCAL_CFLAGS += -Wno-error=return-type
LOCAL_CFLAGS += -DGOOGLE_PROTOBUF_NO_RTTI
LOCAL_CFLAGS += -nostartfiles
LOCAL_LDLIBS += -lm 
LOCAL_LDLIBS += -ldl
LOCAL_LDFLAGS += -rdynamic 
LOCAL_LDLIBS += -lpthread
LOCAL_STATIC_LIBRARIES += libtommath
LOCAL_STATIC_LIBRARIES += libprotobuf
LOCAL_STATIC_LIBRARIES += libprotoc
LOCAL_SHARED_LIBRARIES += libz
LOCAL_SDK_VERSION := 8
LOCAL_NDK_STL_VARIANT := stlport_static
include $(BUILD_EXECUTABLE)


