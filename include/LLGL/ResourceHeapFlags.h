/*
 * ResourceViewHeapFlags.h
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015-2018 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef LLGL_RESOURCE_VIEW_HEAP_FLAGS_H
#define LLGL_RESOURCE_VIEW_HEAP_FLAGS_H


#include "Export.h"
#include <vector>


namespace LLGL
{


class Buffer;
class Texture;
class Sampler;
class PipelineLayout;

/* ----- Enumerations ----- */

/**
\brief Shader resource type enumeration.
\see BindingDescriptor::type
\see ResourceViewDescriptor::type
\see BufferType
*/
enum class ResourceType
{
    //VertexBuffer,       //!< Vertex buffer resource.
    //IndexBuffer,        //!< Index buffer resource.
    ConstantBuffer,     //!< Constant buffer (or uniform buffer) resource.
    StorageBuffer,      //!< Storage buffer resource.
    //StreamOutputBuffer, //!< Stream-output buffer resource.
    Texture,            //!< Texture resource.
    Sampler,            //!< Sampler state resource.
};


/* ----- Structures ----- */

//! Resource view descriptor structure.
struct ResourceViewDescriptor
{
    inline ResourceViewDescriptor() :
        buffer { nullptr }
    {
    }

    //! Resource view type for this layout binding. By default ResourceType::ConstantBuffer.
    ResourceType    type    = ResourceType::ConstantBuffer;

    union
    {
        Buffer*     buffer;
        Texture*    texture;
        Sampler*    sampler;
    };
};

/**
\brief Resource heap descriptor structure.
\remarks For the render systems of modern graphics APIs (i.e. Vulkan and Direct3D 12), a resource heap is the only way to bind hardware resources to a shader pipeline.
The resource heap is a container for one or more resources such as textures, samplers, constant buffers etc.
*/
struct ResourceHeapDescriptor
{
    //! Reference to the pipeline layout.
    PipelineLayout*                     pipelineLayout = nullptr;

    //! List of all resource view descriptors.
    std::vector<ResourceViewDescriptor> resourceViews;
};


} // /namespace LLGL


#endif



// ================================================================================