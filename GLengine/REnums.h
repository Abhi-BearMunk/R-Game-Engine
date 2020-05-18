#pragma once

// Rendering
enum class ImageFormat { RGB, RGBA };
enum class WrapMode { Clamped, Repeat, Mirrored };
enum class FilterMode { Linear, Nearest };
enum class FrameBufferObjectType { R_DEPTH24_STENCIL8, R_NONE };