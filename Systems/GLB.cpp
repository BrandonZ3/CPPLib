#include "GLB.h"  


namespace GLB
{

	//GLBAccessor
	GLBAccessor::GLBAccessor(char* json)
	{
		this->max = NULL;
		this->min = NULL;
		char* bvStr = JSON::GetValue("bufferView", json);
		char* compTStr = JSON::GetValue("componentType", json);
		char* countStr = JSON::GetValue("count", json);
		char* maxStr = JSON::GetValue("max", json);
		char* minStr = JSON::GetValue("min", json);
		char* typeStr = JSON::GetValue("type", json);

		this->bufferView = Strings::StringToUint(bvStr);
		this->componentType = Strings::StringToUint(compTStr);
		this->count = Strings::StringToUint(countStr);

		this->maxCount = 0;
		JSON::DynamicArrayParser(&this->maxCount, (void**)&this->max, maxStr, sizeof(float), JSON::FloatFromJSON);
		if (maxStr != NULL)
		{
			free(maxStr);
		}
		this->minCount = 0;
		JSON::DynamicArrayParser(&this->minCount, (void**)&this->min, minStr, sizeof(float), JSON::FloatFromJSON);
		if (minStr != NULL)
		{
			free(minStr);
		}

		if (Strings::CompareCaseInsensitive(typeStr, "\"SCALAR\"") || Strings::CompareCaseInsensitive(typeStr, "\'SCALAR\'"))
		{
			this->type = GLBAccessorType::SCALAR;
		}

		if (Strings::CompareCaseInsensitive(typeStr, "\"VEC2\"") || Strings::CompareCaseInsensitive(typeStr, "\'VEC2\'"))
		{
			this->type = GLBAccessorType::VEC2;
		}

		if (Strings::CompareCaseInsensitive(typeStr, "\"VEC3\"") || Strings::CompareCaseInsensitive(typeStr, "\'VEC3\'"))
		{
			this->type = GLBAccessorType::VEC3;
		}

		if (Strings::CompareCaseInsensitive(typeStr, "\"VEC4\"") || Strings::CompareCaseInsensitive(typeStr, "\'VEC4\'"))
		{
			this->type = GLBAccessorType::VEC4;
		}

		if (Strings::CompareCaseInsensitive(typeStr, "\"MAT4\"") || Strings::CompareCaseInsensitive(typeStr, "\'MAT4\'"))
		{
			this->type = GLBAccessorType::MAT4;
		}

		free(bvStr);
		free(compTStr);
		free(countStr);
		free(typeStr);
	}

	void GLBAccessor::CallbackConstructor(void* mylocation, char* json)
	{
		GLBAccessor* me = (GLBAccessor*)mylocation;

		me->max = NULL;
		me->min = NULL;
		char* bvStr = JSON::GetValue("bufferView", json);
		char* compTStr = JSON::GetValue("componentType", json);
		char* countStr = JSON::GetValue("count", json);
		char* maxStr = JSON::GetValue("max", json);
		char* minStr = JSON::GetValue("min", json);
		char* typeStr = JSON::GetValue("type", json);

		me->bufferView = Strings::StringToUint(bvStr);
		me->componentType = Strings::StringToUint(compTStr);
		me->count = Strings::StringToUint(countStr);

		me->maxCount = 0;
		JSON::DynamicArrayParser(&me->maxCount, (void**)&me->max, maxStr, sizeof(float), JSON::FloatFromJSON);
		if (maxStr != NULL)
		{
			free(maxStr);
		}
		me->minCount = 0;
		JSON::DynamicArrayParser(&me->minCount, (void**)&me->min, minStr, sizeof(float), JSON::FloatFromJSON);
		if (minStr != NULL)
		{
			free(minStr);
		}

		if (Strings::CompareCaseInsensitive(typeStr, "\"SCALAR\"") || Strings::CompareCaseInsensitive(typeStr, "\'SCALAR\'"))
		{
			me->type = GLBAccessorType::SCALAR;
		}

		if (Strings::CompareCaseInsensitive(typeStr, "\"VEC2\"") || Strings::CompareCaseInsensitive(typeStr, "\'VEC2\'"))
		{
			me->type = GLBAccessorType::VEC2;
		}

		if (Strings::CompareCaseInsensitive(typeStr, "\"VEC3\"") || Strings::CompareCaseInsensitive(typeStr, "\'VEC3\'"))
		{
			me->type = GLBAccessorType::VEC3;
		}

		if (Strings::CompareCaseInsensitive(typeStr, "\"VEC4\"") || Strings::CompareCaseInsensitive(typeStr, "\'VEC4\'"))
		{
			me->type = GLBAccessorType::VEC4;
		}

		if (Strings::CompareCaseInsensitive(typeStr, "\"MAT4\"") || Strings::CompareCaseInsensitive(typeStr, "\'MAT4\'"))
		{
			me->type = GLBAccessorType::MAT4;
		}

		free(bvStr);
		free(compTStr);
		free(countStr);
		free(typeStr);
	}

	uint64_t GLBAccessor::GetComponentTypeSize(uint64_t componentType)
	{
		switch (componentType)
		{
		case 5120:
			return 1;
		case 5121:
			return 1;
		case 5122:
			return 2;
		case 5123:
			return 2;
		case 5125:
			return 4;
		case 5126:
			return 4;
		}
	}

	GLBAccessor::~GLBAccessor()
	{
		if (maxCount > 0)
			free(max);
		if (minCount > 0)
			free(min);
	}

	//GLBAnimationChannelTarget
	GLBAnimationChannelTarget::GLBAnimationChannelTarget()
	{
		node = 0;
		path = GLBAnimationChannelTargetPath::NONE;
	}

	GLBAnimationChannelTarget::GLBAnimationChannelTarget(char* json)
	{

		char* nodeStr = JSON::GetValue("node", json);
		char* pathStr = JSON::GetValue("path", json);

		if (nodeStr != NULL && pathStr != NULL)
		{
			this->node = Strings::StringToUint(nodeStr);

			if (Strings::CompareCaseInsensitive(pathStr, "\"TRANSLATION\"") || Strings::CompareCaseInsensitive(pathStr, "\'TRANSLATION\'"))
			{
				this->path = GLBAnimationChannelTargetPath::TRANSLATION;
			}

			if (Strings::CompareCaseInsensitive(pathStr, "\"ROTATION\"") || Strings::CompareCaseInsensitive(pathStr, "\'ROTATION\'"))
			{
				this->path = GLBAnimationChannelTargetPath::ROTATION;
			}

			if (Strings::CompareCaseInsensitive(pathStr, "\"SCALE\"") || Strings::CompareCaseInsensitive(pathStr, "\'SCALE\'"))
			{
				this->path = GLBAnimationChannelTargetPath::SCALE;
			}
		}
		else
		{
			this->node = 0;
			this->path = GLBAnimationChannelTargetPath::NONE;
		}

		if (nodeStr != NULL)
			free(nodeStr);
		if (pathStr != NULL)
			free(pathStr);
	}

	GLBAnimationChannelTarget::~GLBAnimationChannelTarget()
	{

	}

	//GLBAnimationChannel
	GLBAnimationChannel::GLBAnimationChannel(char* json)
	{
		this->sampler = 0;
		char* samplerStr = JSON::GetValue("sampler", json);
		char* targetStr = JSON::GetValue("target", json);

		if (samplerStr != NULL && targetStr != NULL)
		{
			this->sampler = Strings::StringToUint(samplerStr);
			this->target = GLBAnimationChannelTarget(targetStr);
		}

		if (samplerStr != NULL)
			free(samplerStr);
		if (targetStr != NULL)
			free(targetStr);
	}

	void GLBAnimationChannel::CallbackConstructor(void* mylocation, char* json)
	{
		GLBAnimationChannel* me = (GLBAnimationChannel*)mylocation;
		me->sampler = 0;
		char* samplerStr = JSON::GetValue("sampler", json);
		char* targetStr = JSON::GetValue("target", json);

		if (samplerStr != NULL && targetStr != NULL)
		{
			me->sampler = Strings::StringToUint(samplerStr);
			me->target = GLBAnimationChannelTarget(targetStr);
		}

		if (samplerStr != NULL)
			free(samplerStr);
		if (targetStr != NULL)
			free(targetStr);
	}

	GLBAnimationChannel::~GLBAnimationChannel()
	{
		target.~GLBAnimationChannelTarget();
	}

	//GLBAnimationSampler
	GLBAnimationSampler::GLBAnimationSampler(char* json)
	{
		this->input = 0;
		this->output = 0;
		this->interpolation = GLBAnimationSamplerInterpolationType::INTERPOLATION_NONE;
		char* inputStr = JSON::GetValue("input", json);
		char* interpolationStr = JSON::GetValue("interpolation", json);
		char* outputStr = JSON::GetValue("output", json);

		if (inputStr != NULL && interpolationStr != NULL && outputStr != NULL)
		{
			this->input = Strings::StringToUint(inputStr);
			if (Strings::CompareCaseInsensitive(interpolationStr, "\"STEP\"") || Strings::CompareCaseInsensitive(interpolationStr, "\'STEP\'"))
			{
				this->interpolation = GLBAnimationSamplerInterpolationType::STEP;
			}
			if (Strings::CompareCaseInsensitive(interpolationStr, "\"LINEAR\"") || Strings::CompareCaseInsensitive(interpolationStr, "\'LINEAR\'"))
			{
				this->interpolation = GLBAnimationSamplerInterpolationType::LINEAR;
			}
			this->output = Strings::StringToUint(outputStr);
		}

		if (inputStr != NULL)
			free(inputStr);
		if (interpolationStr)
			free(interpolationStr);
		if (outputStr != NULL)
			free(outputStr);
	}

	void GLBAnimationSampler::CallbackConstructor(void* mylocation, char* json)
	{
		GLBAnimationSampler* me = (GLBAnimationSampler*)mylocation;
		me->input = 0;
		me->output = 0;
		me->interpolation = GLBAnimationSamplerInterpolationType::INTERPOLATION_NONE;
		char* inputStr = JSON::GetValue("input", json);
		char* interpolationStr = JSON::GetValue("interpolation", json);
		char* outputStr = JSON::GetValue("output", json);

		if (inputStr != NULL && interpolationStr != NULL && outputStr != NULL)
		{
			me->input = Strings::StringToUint(inputStr);
			if (Strings::CompareCaseInsensitive(interpolationStr, "\"STEP\"") || Strings::CompareCaseInsensitive(interpolationStr, "\'STEP\'"))
			{
				me->interpolation = GLBAnimationSamplerInterpolationType::STEP;
			}
			if (Strings::CompareCaseInsensitive(interpolationStr, "\"LINEAR\"") || Strings::CompareCaseInsensitive(interpolationStr, "\'LINEAR\'"))
			{
				me->interpolation = GLBAnimationSamplerInterpolationType::LINEAR;
			}
			me->output = Strings::StringToUint(outputStr);
		}

		if (inputStr != NULL)
			free(inputStr);
		if (interpolationStr)
			free(interpolationStr);
		if (outputStr != NULL)
			free(outputStr);
	}

	GLBAnimationSampler::~GLBAnimationSampler()
	{

	}

	//GLBAnimation
	GLBAnimation::GLBAnimation(char* json)
	{
		this->channels = NULL;
		this->animationName = NULL;
		this->samplers = NULL;
		char* channels = JSON::GetValue("channels", json);
		JSON::DynamicArrayParser(&this->channelCount, (void**)&this->channels, channels, sizeof(GLBAnimationChannel), GLBAnimationChannel::CallbackConstructor);
		if (channels != NULL)
		{
			free(channels);
		}

		this->animationName = JSON::GetValue("name", json);

		char* samplers = JSON::GetValue("samplers", json);
		JSON::DynamicArrayParser(&this->samplerCount, (void**)&this->samplers, samplers, sizeof(GLBAnimationSampler), GLBAnimationSampler::CallbackConstructor);
		if (samplers != NULL)
		{
			free(samplers);
		}
	}

	void GLBAnimation::CallbackConstructor(void* mylocation, char* json)
	{
		GLBAnimation* me = (GLBAnimation*)mylocation;

		me->channels = NULL;
		me->animationName = NULL;
		me->samplers = NULL;
		char* channels = JSON::GetValue("channels", json);
		JSON::DynamicArrayParser(&me->channelCount, (void**)&me->channels, channels, sizeof(GLBAnimationChannel), GLBAnimationChannel::CallbackConstructor);
		if (channels != NULL)
		{
			free(channels);
		}

		me->animationName = JSON::GetValue("name", json);

		char* samplers = JSON::GetValue("samplers", json);
		JSON::DynamicArrayParser(&me->samplerCount, (void**)&me->samplers, samplers, sizeof(GLBAnimationSampler), GLBAnimationSampler::CallbackConstructor);
		if (samplers != NULL)
		{
			free(samplers);
		}
	}

	GLBAnimation::~GLBAnimation()
	{
		if (channels != NULL)
		{
			for (int i = 0; i < channelCount; i++)
				channels[i].~GLBAnimationChannel();
			free(channels);
		}


		if (samplers != NULL)
		{
			for (int i = 0; i < samplerCount; i++)
				samplers[i].~GLBAnimationSampler();
			free(samplers);
		}

		if (animationName != NULL)
		{
			free(animationName);
		}
	}

	//GLBAsset
	GLBAsset::GLBAsset()
	{
		this->generatorName = NULL;
		this->version = NULL;
	}

	GLBAsset::GLBAsset(char* json)
	{
		this->generatorName = NULL;
		this->version = NULL;
		this->generatorName = JSON::GetValue("generator", json);
		this->version = JSON::GetValue("version", json);
	}

	GLBAsset::~GLBAsset()
	{
		if (generatorName != NULL)
			free(generatorName);
		if (version != NULL)
			free(version);
	}

	//GLBBufferView
	GLBBufferView::GLBBufferView(char* json)
	{
		char* bufferStr = JSON::GetValue("buffer", json);
		char* byteLengthStr = JSON::GetValue("byteLength", json);
		char* byteOffsetStr = JSON::GetValue("byteOffset", json);
		char* targetStr = JSON::GetValue("target", json);

		if (bufferStr != NULL)
		{
			this->buffer = Strings::StringToUint(bufferStr);
			free(bufferStr);
		}

		if (byteLengthStr != NULL)
		{
			this->byteLength = Strings::StringToUint(byteLengthStr);
			free(byteLengthStr);
		}

		if (byteOffsetStr != NULL)
		{
			this->byteOffset = Strings::StringToUint(byteOffsetStr);
			free(byteOffsetStr);
		}

		if (targetStr != NULL)
		{
			this->useTarget = true;
			this->target = Strings::StringToUint(bufferStr);
			free(targetStr);
		}
	}

	void GLBBufferView::CallbackConstructor(void* mylocation, char* json)
	{
		GLBBufferView* me = (GLBBufferView*)mylocation;
		char* bufferStr = JSON::GetValue("buffer", json);
		char* byteLengthStr = JSON::GetValue("byteLength", json);
		char* byteOffsetStr = JSON::GetValue("byteOffset", json);
		char* targetStr = JSON::GetValue("target", json);

		if (bufferStr != NULL)
		{
			me->buffer = Strings::StringToUint(bufferStr);
			free(bufferStr);
		}

		if (byteLengthStr != NULL)
		{
			me->byteLength = Strings::StringToUint(byteLengthStr);
			free(byteLengthStr);
		}

		if (byteOffsetStr != NULL)
		{
			me->byteOffset = Strings::StringToUint(byteOffsetStr);
			free(byteOffsetStr);
		}

		if (targetStr != NULL)
		{
			me->useTarget = true;
			me->target = Strings::StringToUint(bufferStr);
			free(targetStr);
		}
	}

	//GLBBuffer
	GLBBuffer::GLBBuffer(char* json)
	{
		char* byteLengthString = JSON::GetValue("byteLength", json);

		if (byteLengthString != NULL)
		{
			this->byteLength = Strings::StringToUint(byteLengthString);
			free(byteLengthString);
		}
	}

	void GLBBuffer::CallbackConstructor(void* mylocation, char* json)
	{
		GLBBuffer* me = (GLBBuffer*)mylocation;

		char* byteLengthString = JSON::GetValue("byteLength", json);

		if (byteLengthString != NULL)
		{
			me->byteLength = Strings::StringToUint(byteLengthString);
			free(byteLengthString);
		}
	}

	GLBBuffer::~GLBBuffer()
	{

	}

	//GLBImage
	GLBImage::GLBImage(char* json)
	{
		this->bufferView = 0;
		this->name = NULL;
		this->mimeType = NULL;

		char* bufferView = JSON::GetValue("bufferView", json);
		char* name = JSON::GetValue("name", json);
		char* mimeType = JSON::GetValue("mimeType", json);

		if (bufferView != NULL)
		{
			this->bufferView = Strings::StringToUint(bufferView);
			free(bufferView);
		}

		if (name != NULL)
			this->name = name;
		if (mimeType != NULL)
			this->mimeType = mimeType;
	}

	void GLBImage::CallbackConstructor(void* mylocation, char* json)
	{
		GLBImage* me = (GLBImage*)mylocation;
		me->bufferView = 0;
		me->name = NULL;
		me->mimeType = NULL;

		char* bufferView = JSON::GetValue("bufferView", json);
		char* name = JSON::GetValue("name", json);
		char* mimeType = JSON::GetValue("mimeType", json);

		if (bufferView != NULL)
		{
			me->bufferView = Strings::StringToUint(bufferView);
			free(bufferView);
		}

		if (name != NULL)
			me->name = name;
		if (mimeType != NULL)
			me->mimeType = mimeType;
	}

	GLBImage::~GLBImage()
	{
		if (this->name != NULL)
			free(this->name);
		if (this->mimeType != NULL)
			free(this->mimeType);
	}

	//GLBTexture
	GLBTexture::GLBTexture(char* json)
	{
		this->sampler = 0;
		this->source = 0;

		char* sampler = JSON::GetValue("sampler", json);
		char* source = JSON::GetValue("source", json);

		if (sampler != NULL)
		{
			this->sampler = Strings::StringToUint(sampler);
			free(sampler);
		}

		if (source != NULL)
		{
			this->source = Strings::StringToUint(source);
			free(source);
		}
	}

	void GLBTexture::CallbackConstructor(void* mylocation, char* json)
	{
		GLBTexture* me = (GLBTexture*)mylocation;
		me->sampler = 0;
		me->source = 0;

		char* sampler = JSON::GetValue("sampler", json);
		char* source = JSON::GetValue("source", json);

		if (sampler != NULL)
		{
			me->sampler = Strings::StringToUint(sampler);
			free(sampler);
		}

		if (source != NULL)
		{
			me->source = Strings::StringToUint(source);
			free(source);
		}
	}

	GLBTexture::~GLBTexture()
	{

	}

	//GLBMetallicRoughness
	GLBMetallicRoughness::GLBMetallicRoughness()
	{
		this->metallicFactor = 0;
		this->roughnessFactor = 0;
		this->baseColorTexture = GLBBaseColorTexture();
	}

	GLBMetallicRoughness::GLBMetallicRoughness(char* json)
	{
		this->metallicFactor = 0;
		this->roughnessFactor = 0;
		this->baseColorTexture = GLBBaseColorTexture();

		char* metallicFactor = JSON::GetValue("metallicFactor", json);
		char* roughnessFactor = JSON::GetValue("roughnessFactor", json);
		char* baseColorTexture = JSON::GetValue("baseColorTexture", json);

		if (metallicFactor != NULL)
		{
			this->metallicFactor = Strings::StringToUint(metallicFactor);
			free(metallicFactor);
		}

		if (roughnessFactor != NULL)
		{
			this->roughnessFactor = Strings::StringToUint(roughnessFactor);
			free(roughnessFactor);
		}

		if (baseColorTexture != NULL)
		{
			char* index = JSON::GetValue("index", baseColorTexture);

			if (index != NULL)
			{
				this->baseColorTexture.index = Strings::StringToUint(index);
				free(index);
			}
			free(baseColorTexture);
		}
	}

	void GLBMetallicRoughness::CallbackConstructor(void* mylocation, char* json)
	{
		GLBMetallicRoughness* me = (GLBMetallicRoughness*)mylocation;
		me->metallicFactor = 0;
		me->roughnessFactor = 0;
		me->baseColorTexture = GLBBaseColorTexture();

		char* metallicFactor = JSON::GetValue("metallicFactor", json);
		char* roughnessFactor = JSON::GetValue("roughnessFactor", json);
		char* baseColorTexture = JSON::GetValue("baseColorTexture", json);

		if (metallicFactor != NULL)
		{
			me->metallicFactor = Strings::StringToUint(metallicFactor);
			free(metallicFactor);
		}

		if (roughnessFactor != NULL)
		{
			me->roughnessFactor = Strings::StringToUint(roughnessFactor);
			free(roughnessFactor);
		}

		if (baseColorTexture != NULL)
		{
			char* index = JSON::GetValue("index", baseColorTexture);

			if (index != NULL)
			{
				me->baseColorTexture.index = Strings::StringToUint(index);
				free(index);
			}
			free(baseColorTexture);
		}
	}

	GLBMetallicRoughness::~GLBMetallicRoughness()
	{

	}

	//GLBMaterial
	GLBMaterial::GLBMaterial(char* json)
	{
		this->doubleSided = false;
		this->name = NULL;
		this->metallicRoughnessUsed = false;
		this->normalTextureUsed = false;

		char* name = JSON::GetValue("name", json);
		char* doubleSided = JSON::GetValue("doubleSided", json);
		char* pbrMetallicRoughness = JSON::GetValue("pbrMetallicRoughness", json);
		char* normalTexture = JSON::GetValue("normalTexture", json);

		if (name != NULL)
			this->name = name;

		if (doubleSided != NULL)
		{
			this->doubleSided = Strings::CompareCaseInsensitive("true", doubleSided);
			free(doubleSided);
		}

		if (pbrMetallicRoughness != NULL)
		{
			this->metallicRoughnessUsed = true;
			this->pbrMetallicRoughness = GLBMetallicRoughness(pbrMetallicRoughness);
			free(pbrMetallicRoughness);
		}

		if (normalTexture != NULL)
		{
			this->normalTextureUsed = true;
			char* index = JSON::GetValue("index", normalTexture);

			if (index != NULL)
			{
				this->normalTexture.index = Strings::StringToUint(index);
				free(index);
			}
			free(normalTexture);
		}
	}

	void GLBMaterial::CallbackConstructor(void* mylocation, char* json)
	{
		GLBMaterial* me = (GLBMaterial*)mylocation;
		me->doubleSided = false;
		me->name = NULL;
		me->metallicRoughnessUsed = false;
		me->normalTextureUsed = false;

		char* name = JSON::GetValue("name", json);
		char* doubleSided = JSON::GetValue("doubleSided", json);
		char* pbrMetallicRoughness = JSON::GetValue("pbrMetallicRoughness", json);
		char* normalTexture = JSON::GetValue("normalTexture", json);

		if (name != NULL)
			me->name = name;

		if (doubleSided != NULL)
		{
			me->doubleSided = Strings::CompareCaseInsensitive("true", doubleSided);
			free(doubleSided);
		}

		if (pbrMetallicRoughness != NULL)
		{
			me->metallicRoughnessUsed = true;
			me->pbrMetallicRoughness = GLBMetallicRoughness(pbrMetallicRoughness);
			free(pbrMetallicRoughness);
		}

		if (normalTexture != NULL)
		{
			me->normalTextureUsed = true;
			char* index = JSON::GetValue("index", normalTexture);

			if (index != NULL)
			{
				me->normalTexture.index = Strings::StringToUint(index);
				free(index);
			}
			free(normalTexture);
		}
	}

	GLBMaterial::~GLBMaterial()
	{
		if (this->name != NULL)
		{
			free(this->name);
		}
	}

	//GLBMeshPrimitive
	GLBMeshPrimitive::GLBMeshPrimitive(char* json)
	{
		this->attributes = NULL;
		this->values = NULL;
		this->indices = 0;
		this->hasMaterial = false;
		this->material = 0;

		char* indices = JSON::GetValue("indices", json);
		char* material = JSON::GetValue("material", json);
		char* attributes = JSON::GetValue("attributes", json);

		if (indices != NULL)
		{
			this->indices = Strings::StringToUint(indices);
			free(indices);
		}

		if (material != NULL)
		{
			this->hasMaterial = true;
			this->material = Strings::StringToUint(material);
			free(material);
		}

		if (attributes != NULL)
		{
			this->attributes = JSON::GetKeys(attributes);
			this->values = (uint64_t*)malloc(this->attributes->count * sizeof(uint64_t));
			for (int i = 0; i < this->attributes->count; i++)
			{
				char* value = JSON::GetValue((char*)this->attributes->items[i], attributes);
				if (value != NULL)
				{
					this->values[i] = Strings::StringToUint(value);
					free(value);
				}
			}
			free(attributes);
		}
	}

	void GLBMeshPrimitive::CallbackConstructor(void* mylocation, char* json)
	{
		GLBMeshPrimitive* me = (GLBMeshPrimitive*)mylocation;

		me->attributes = NULL;
		me->values = NULL;
		me->indices = 0;
		me->hasMaterial = false;
		me->material = 0;

		char* indices = JSON::GetValue("indices", json);
		char* material = JSON::GetValue("material", json);
		char* attributes = JSON::GetValue("attributes", json);

		if (indices != NULL)
		{
			me->indices = Strings::StringToUint(indices);
			free(indices);
		}

		if (material != NULL)
		{
			me->hasMaterial = true;
			me->material = Strings::StringToUint(material);
			free(material);
		}

		if (attributes != NULL)
		{
			me->attributes = JSON::GetKeys(attributes);
			me->values = (uint64_t*)malloc(me->attributes->count * sizeof(uint64_t));
			for (int i = 0; i < me->attributes->count; i++)
			{
				char* value = JSON::GetValue((char*)me->attributes->items[i], attributes);
				if (value != NULL)
				{
					me->values[i] = Strings::StringToUint(value);
					free(value);
				}
			}
			free(attributes);
		}
	}

	GLBMeshPrimitive::~GLBMeshPrimitive()
	{
		if (attributes != NULL)
		{
			attributes->FreeEverything();
			delete attributes;
		}

		if (values != NULL)
		{
			free(values);
		}
	}

	//GLBMesh
	GLBMesh::GLBMesh(char* json)
	{
		this->name = NULL;
		this->primitives = NULL;
		this->name = JSON::GetValue("name", json);

		char* primitives = JSON::GetValue("primitives", json);
		JSON::DynamicArrayParser(&this->primitiveCount, (void**)&this->primitives, primitives, sizeof(GLBMeshPrimitive), GLBMeshPrimitive::CallbackConstructor);
		if (primitives != NULL)
		{
			free(primitives);
		}
	}

	void GLBMesh::CallbackConstructor(void* mylocation, char* json)
	{
		GLBMesh* me = (GLBMesh*)mylocation;

		me->name = NULL;
		me->primitives = NULL;
		me->name = JSON::GetValue("name", json);

		char* primitives = JSON::GetValue("primitives", json);
		JSON::DynamicArrayParser(&me->primitiveCount, (void**)&me->primitives, primitives, sizeof(GLBMeshPrimitive), GLBMeshPrimitive::CallbackConstructor);
		if (primitives != NULL)
		{
			free(primitives);
		}
	}

	GLBMesh::~GLBMesh()
	{
		if (name != NULL)
		{
			free(name);
		}

		if (primitives != NULL)
		{
			for (size_t i = 0; i < primitiveCount; i++)
			{
				primitives[i].~GLBMeshPrimitive();
			}
			free(primitives);
		}
	}

	//GLBNode
	GLBNode::GLBNode(char* json)
	{
		this->children = NULL;
		this->name = NULL;
		this->rotation = NULL;
		this->scale = NULL;
		this->translation = NULL;
		this->hasMesh = false;
		this->hasSkin = false;
		this->translationOverride = false;
		this->rotationOverride = false;
		this->scaleOverride = false;
		char* children = JSON::GetValue("children", json);
		JSON::DynamicArrayParser(&this->childrenCount, (void**)&this->children, children, sizeof(uint64_t), JSON::Uint64_tFromJSON);
		if (children != NULL)
		{
			free(children);
		}

		this->name = JSON::GetValue("name", json);

		char* rotation = JSON::GetValue("rotation", json);
		JSON::DynamicArrayParser(&this->rotationCount, (void**)&this->rotation, rotation, sizeof(float), JSON::FloatFromJSON);
		if (rotation != NULL)
		{
			free(rotation);
		}

		char* scale = JSON::GetValue("scale", json);
		JSON::DynamicArrayParser(&this->scaleCount, (void**)&this->scale, scale, sizeof(float), JSON::FloatFromJSON);
		if (scale != NULL)
		{
			free(scale);
		}

		char* translation = JSON::GetValue("translation", json);
		JSON::DynamicArrayParser(&this->translationCount, (void**)&this->translation, translation, sizeof(float), JSON::FloatFromJSON);
		if (translation != NULL)
		{
			free(translation);
		}

		char* mesh = JSON::GetValue("mesh", json);
		if (mesh != NULL)
		{
			this->hasMesh = true;
			this->mesh = Strings::StringToUint(mesh);
			free(mesh);
		}
		char* skin = JSON::GetValue("skin", json);
		if (skin != NULL)
		{
			this->hasSkin = true;
			this->skin = Strings::StringToUint(skin);
			free(skin);
		}
	}

	void GLBNode::CallbackConstructor(void* mylocation, char* json)
	{
		GLBNode* me = (GLBNode*)mylocation;

		me->children = NULL;
		me->name = NULL;
		me->rotation = NULL;
		me->scale = NULL;
		me->translation = NULL;
		me->hasMesh = false;
		me->hasSkin = false;
		me->translationOverride = false;
		me->rotationOverride = false;
		me->scaleOverride = false;
		char* children = JSON::GetValue("children", json);
		JSON::DynamicArrayParser(&me->childrenCount, (void**)&me->children, children, sizeof(uint64_t), JSON::Uint64_tFromJSON);
		if (children != NULL)
		{
			free(children);
		}

		me->name = JSON::GetValue("name", json);

		char* rotation = JSON::GetValue("rotation", json);
		JSON::DynamicArrayParser(&me->rotationCount, (void**)&me->rotation, rotation, sizeof(float), JSON::FloatFromJSON);
		if (rotation != NULL)
		{
			free(rotation);
		}

		char* scale = JSON::GetValue("scale", json);
		JSON::DynamicArrayParser(&me->scaleCount, (void**)&me->scale, scale, sizeof(float), JSON::FloatFromJSON);
		if (scale != NULL)
		{
			free(scale);
		}

		char* translation = JSON::GetValue("translation", json);
		JSON::DynamicArrayParser(&me->translationCount, (void**)&me->translation, translation, sizeof(float), JSON::FloatFromJSON);
		if (translation != NULL)
		{
			free(translation);
		}

		char* mesh = JSON::GetValue("mesh", json);
		if (mesh != NULL)
		{
			me->hasMesh = true;
			me->mesh = Strings::StringToUint(mesh);
			free(mesh);
		}
		char* skin = JSON::GetValue("skin", json);
		if (skin != NULL)
		{
			me->hasSkin = true;
			me->skin = Strings::StringToUint(skin);
			free(skin);
		}
	}

	GLBNode::~GLBNode()
	{
		if (children != NULL)
			free(children);
		if (name != NULL)
			free(name);
		if (rotation != NULL)
			free(rotation);
		if (scale != NULL)
			free(scale);
		if (translation != NULL)
			free(translation);
	}

	//GLBScene
	GLBScene::GLBScene(char* json)
	{
		this->name = NULL;
		this->nodes = NULL;
		this->name = JSON::GetValue("name", json);

		char* nodes = JSON::GetValue("nodes", json);
		JSON::DynamicArrayParser(&this->nodeCount, (void**)&this->nodes, nodes, sizeof(uint64_t), JSON::Uint64_tFromJSON);
		if (nodes != NULL)
		{
			free(nodes);
		}
	}

	void GLBScene::CallbackConstructor(void* mylocation, char* json)
	{
		GLBScene* me = (GLBScene*)mylocation;

		me->name = NULL;
		me->nodes = NULL;
		me->name = JSON::GetValue("name", json);

		char* nodes = JSON::GetValue("nodes", json);
		JSON::DynamicArrayParser(&me->nodeCount, (void**)&me->nodes, nodes, sizeof(uint64_t), JSON::Uint64_tFromJSON);
		if (nodes != NULL)
		{
			free(nodes);
		}
	}

	GLBScene::~GLBScene()
	{
		if (name != NULL)
		{
			free(name);
		}

		if (nodes != NULL)
		{
			free(nodes);
		}
	}

	//GLBSkin
	GLBSkin::GLBSkin(char* json)
	{
		this->name = NULL;
		this->joints = NULL;
		this->name = JSON::GetValue("name", json);

		char* invbStr = JSON::GetValue("inverseBindMatrices", json);
		if (invbStr != NULL)
		{
			this->inverseBindMatrices = Strings::StringToUint(invbStr);
			free(invbStr);
		}

		char* joints = JSON::GetValue("joints", json);
		JSON::DynamicArrayParser(&this->jointCount, (void**)&this->joints, joints, sizeof(uint64_t), JSON::Uint64_tFromJSON);
		if (joints != NULL)
		{
			free(joints);
		}
	}

	void GLBSkin::CallbackConstructor(void* mylocation, char* json)
	{
		GLBSkin* me = (GLBSkin*)mylocation;

		me->name = NULL;
		me->joints = NULL;
		me->name = JSON::GetValue("name", json);

		char* invbStr = JSON::GetValue("inverseBindMatrices", json);
		if (invbStr != NULL)
		{
			me->inverseBindMatrices = Strings::StringToUint(invbStr);
			free(invbStr);
		}

		char* joints = JSON::GetValue("joints", json);
		JSON::DynamicArrayParser(&me->jointCount, (void**)&me->joints, joints, sizeof(uint64_t), JSON::Uint64_tFromJSON);
		if (joints != NULL)
		{
			free(joints);
		}
	}

	GLBSkin::~GLBSkin()
	{
		if (name != NULL)
		{
			free(name);
		}

		if (joints != NULL)
		{
			free(joints);
		}
	}

	//GLB
	GLB::GLB(DBuffer* json, DBuffer* bindata)
	{
		this->binaryData = bindata->Slice(0, bindata->count);
		char* accessors = JSON::GetValue("accessors", (char*)json->DataPointer(0));
		JSON::DynamicArrayParser(&this->accessorCount, (void**)&this->accessors, accessors, sizeof(GLBAccessor), GLBAccessor::CallbackConstructor);
		if (accessors != NULL)
		{
			free(accessors);
		}

		char* animations = JSON::GetValue("animations", (char*)json->DataPointer(0));
		JSON::DynamicArrayParser(&this->animationCount, (void**)&this->animations, animations, sizeof(GLBAnimation), GLBAnimation::CallbackConstructor);
		if (animations != NULL)
		{
			free(animations);
		}

		char* asset = JSON::GetValue("asset", (char*)json->DataPointer(0));
		if (asset != NULL)
		{
			this->asset = new GLBAsset(asset);
			free(asset);
		}

		char* bufferViews = JSON::GetValue("bufferViews", (char*)json->DataPointer(0));
		JSON::DynamicArrayParser(&this->bufferViewCount, (void**)&this->bufferViews, bufferViews, sizeof(GLBBufferView), GLBBufferView::CallbackConstructor);
		if (bufferViews != NULL)
		{
			free(bufferViews);
		}

		char* buffers = JSON::GetValue("buffers", (char*)json->DataPointer(0));
		JSON::DynamicArrayParser(&this->bufferCount, (void**)&this->buffers, buffers, sizeof(GLBBuffer), GLBBuffer::CallbackConstructor);
		if (buffers != NULL)
		{
			free(buffers);
		}

		char* meshes = JSON::GetValue("meshes", (char*)json->DataPointer(0));
		JSON::DynamicArrayParser(&this->meshCount, (void**)&this->meshes, meshes, sizeof(GLBMesh), GLBMesh::CallbackConstructor);
		if (meshes != NULL)
		{
			free(meshes);
		}

		char* nodes = JSON::GetValue("nodes", (char*)json->DataPointer(0));
		JSON::DynamicArrayParser(&this->nodeCount, (void**)&this->nodes, nodes, sizeof(GLBNode), GLBNode::CallbackConstructor);
		if (nodes != NULL)
		{
			free(nodes);
		}

		char* scene = JSON::GetValue("scene", (char*)json->DataPointer(0));
		if (scene != NULL)
		{
			this->scene = Strings::StringToUint(scene);
			free(scene);
		}

		char* scenes = JSON::GetValue("scenes", (char*)json->DataPointer(0));
		JSON::DynamicArrayParser(&this->sceneCount, (void**)&this->scenes, scenes, sizeof(GLBScene), GLBScene::CallbackConstructor);
		if (scenes != NULL)
		{
			free(scenes);
		}

		char* skins = JSON::GetValue("skins", (char*)json->DataPointer(0));
		JSON::DynamicArrayParser(&this->skinCount, (void**)&this->skins, skins, sizeof(GLBSkin), GLBSkin::CallbackConstructor);
		if (skins != NULL)
		{
			free(skins);
		}


		char* materials = JSON::GetValue("materials", (char*)json->DataPointer(0));
		JSON::DynamicArrayParser(&this->materialCount, (void**)&this->materials, materials, sizeof(GLBMaterial), GLBMaterial::CallbackConstructor);
		if (materials != NULL)
		{
			free(materials);
		}


		char* textures = JSON::GetValue("textures", (char*)json->DataPointer(0));
		JSON::DynamicArrayParser(&this->textureCount, (void**)&this->textures, textures, sizeof(GLBTexture), GLBTexture::CallbackConstructor);
		if (textures != NULL)
		{
			free(textures);
		}


		char* images = JSON::GetValue("images", (char*)json->DataPointer(0));
		JSON::DynamicArrayParser(&this->imageCount, (void**)&this->images, images, sizeof(GLBImage), GLBImage::CallbackConstructor);
		if (images != NULL)
		{
			free(images);
		}
	}

	GLB* GLB::GetGLB(char* filename)
	{
		GLB* output = NULL;

		bool exists = Files::FileExists(filename);
		if (exists)
		{
			DBuffer* rawfile = Files::ReadFile(filename);
			RDBuffer reader(rawfile);
			char* signature = NULL;
			reader.ReadString(&signature, 4);
			if (Strings::Compare(signature, "glTF"))
			{
				uint32_t version;
				uint32_t filesize;
				uint32_t jsonlength;
				char* type = NULL;
				uint64_t jsonstart;
				uint32_t binlength;
				char* btype = NULL;
				uint64_t binstart;

				reader.ReadDWord(&version);
				reader.ReadDWord(&filesize);
				if (filesize == rawfile->count)
				{
					reader.ReadDWord(&jsonlength);
					reader.ReadString(&type, 4);
					jsonstart = reader.GetPosition();
					reader.ShiftPosition(jsonlength);
					reader.ReadDWord(&binlength);
					reader.ReadString(&btype, 4);
					binstart = reader.GetPosition();

					if (version == 2 && Strings::Compare(type, "JSON") && Strings::Compare(btype, "BIN"))
					{
						DBuffer* jsononly = rawfile->Slice(jsonstart, jsonlength);
						jsononly->Add((unsigned char)0);
						DBuffer* binonly = rawfile->Slice(binstart, binlength);

						output = new GLB(jsononly, binonly);

						delete jsononly;
						delete binonly;
					}

					free(type);
					free(btype);
				}
			}
			free(signature);
			delete rawfile;
		}

		return output;
	}

	GLB::~GLB()
	{
		if (binaryData != NULL)
			delete binaryData;

		if (accessors != NULL)
		{
			for (size_t i = 0; i < accessorCount; i++)
			{
				accessors[i].~GLBAccessor();
			}
			free(accessors);
		}

		if (animations != NULL)
		{
			for (size_t i = 0; i < animationCount; i++)
			{
				animations[i].~GLBAnimation();
			}
			free(animations);
		}

		delete asset;

		if (bufferViews != NULL)
		{
			for (size_t i = 0; i < bufferViewCount; i++)
			{
				bufferViews[i].~GLBBufferView();
			}
			free(bufferViews);
		}

		if (buffers != NULL)
		{
			for (size_t i = 0; i < bufferCount; i++)
			{
				buffers[i].~GLBBuffer();
			}
			free(buffers);
		}

		if (meshes != NULL)
		{
			for (size_t i = 0; i < meshCount; i++)
			{
				meshes[i].~GLBMesh();
			}
			free(meshes);
		}

		if (nodes != NULL)
		{
			for (size_t i = 0; i < nodeCount; i++)
			{
				nodes[i].~GLBNode();
			}
			free(nodes);
		}

		if (scenes != NULL)
		{
			for (size_t i = 0; i < sceneCount; i++)
			{
				scenes[i].~GLBScene();
			}
			free(scenes);
		}

		if (skins != NULL)
		{
			for (size_t i = 0; i < skinCount; i++)
			{
				skins[i].~GLBSkin();
			}
			free(skins);
		}

		if (materials != NULL)
		{
			for (size_t i = 0; i < materialCount; i++)
			{
				materials[i].~GLBMaterial();
			}
			free(materials);
		}

		if (textures != NULL)
		{
			for (size_t i = 0; i < textureCount; i++)
			{
				textures[i].~GLBTexture();
			}
			free(textures);
		}

		if (images != NULL)
		{
			for (size_t i = 0; i < imageCount; i++)
			{
				images[i].~GLBImage();
			}
			free(images);
		}
	}

	//GLBTreeNode
	void GLBTreeNode::SetupChildren(GLB* glb, int64_t* mesh, int64_t* skin, uint64_t* count)
	{
		this->children = (GLBTreeNode*)malloc(this->myself->childrenCount * sizeof(GLBTreeNode));
		if (this->children != NULL)
		{
			for (int i = 0; i < this->myself->childrenCount; i++)
			{
				this->children[i] = GLBTreeNode();
				this->children[i].index = this->myself->children[i];
				this->children[i].myself = &glb->nodes[this->children[i].index];
				this->children[i].SetupChildren(glb, mesh, skin, count);
			}
		}

		(*count)++;

		if (this->myself->hasMesh)
		{
			*mesh = this->myself->mesh;
		}

		if (this->myself->hasSkin)
		{
			*skin = this->myself->skin;
		}
	}

	void GLBTreeNode::CalculateWorldMatrix(GLB* glb, DirectX::XMMATRIX parentMatrix)
	{

		DirectX::XMMATRIX scaleM = DirectX::XMMatrixIdentity();
		DirectX::XMMATRIX rotationM = DirectX::XMMatrixIdentity();
		DirectX::XMMATRIX translationM = DirectX::XMMatrixIdentity();

		if (!this->myself->translationOverride && this->myself->translationCount > 0)
		{
			DirectX::XMVECTOR translation = DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)this->myself->translation);
			translationM = DirectX::XMMatrixTranslationFromVector(translation);
		}
		else if (this->myself->translationOverride)
		{
			DirectX::XMVECTOR translation = DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)this->myself->translationO);
			translationM = DirectX::XMMatrixTranslationFromVector(translation);
			this->myself->translationOverride = false;
		}

		if (!this->myself->rotationOverride && this->myself->rotationCount > 0)
		{
			rotationM = DirectX::XMMatrixRotationQuaternion(*(DirectX::FXMVECTOR*)this->myself->rotation);
		}
		else if (this->myself->rotationOverride)
		{
			rotationM = DirectX::XMMatrixRotationQuaternion(*(DirectX::FXMVECTOR*)this->myself->rotationO);
			this->myself->rotationOverride = false;
		}

		if (!this->myself->scaleOverride && this->myself->scaleCount > 0)
		{
			DirectX::XMVECTOR scale = DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)this->myself->scale);
			scaleM = DirectX::XMMatrixScalingFromVector(scale);
		}
		else if (this->myself->scaleOverride)
		{
			DirectX::XMVECTOR scale = DirectX::XMLoadFloat3((DirectX::XMFLOAT3*)this->myself->scaleO);
			scaleM = DirectX::XMMatrixScalingFromVector(scale);
			this->myself->scaleOverride = false;
		}

		this->myself->worldMatrix = scaleM * rotationM * translationM;
		this->myself->worldMatrix = this->myself->worldMatrix * parentMatrix;

		for (int i = 0; i < this->myself->childrenCount; i++)
		{
			this->children[i].CalculateWorldMatrix(glb, this->myself->worldMatrix);
		}
	}

	GLBTreeNode::~GLBTreeNode()
	{
		if (myself != NULL)
		{
			for (int i = 0; i < this->myself->childrenCount; i++)
			{
				this->children[i].~GLBTreeNode();
			}
			if (this->children != NULL)
			{
				free(this->children);
			}
		}
	}

	GLBTreeNode* SetupNodeTree(GLB* glb, uint64_t rootNodeIndex, int64_t* mesh, int64_t* skin, uint64_t* count)
	{
		GLBTreeNode* node = new GLBTreeNode();
		GLBNode* rootNode = &glb->nodes[rootNodeIndex];
		node->index = rootNodeIndex;
		node->myself = rootNode;
		node->SetupChildren(glb, mesh, skin, count);
		return node;
	}

	GLBTreeNode* GetNodeTree(GLB* glb)
	{
		if (glb->sceneCount > 0)
		{
			GLBScene* scene = &glb->scenes[glb->scene];

			if (scene->nodeCount == 1)
			{
				int64_t mesh = -1;
				int64_t skin = -1;
				uint64_t count = 0;
				GLBTreeNode* tree = SetupNodeTree(glb, scene->nodes[0], &mesh, &skin, &count);

				if (mesh != -1 && skin != -1 && count == glb->nodeCount)
				{
					return tree;
				}
				else
					delete tree;
			}
		}
		return NULL;
	}
}
//Keyboard