#pragma once 
#include <stdint.h>
#include <DirectXMath.h>

#include "../Containers/PointerList.h"
#include "../Containers/DBuffer.h"
#include "../Parsing/JSON.h"
#include "../IO/Files.h"
#include "../Containers/RDBuffer.h"

namespace GLB
{
	enum GLBAccessorType
	{
		SCALAR,
		VEC2,
		VEC3,
		VEC4,
		MAT4
	};

	class GLBAccessor
	{
	public:
		uint64_t bufferView;
		uint64_t componentType;
		uint64_t count;
		uint64_t maxCount;
		float* max = NULL;
		uint64_t minCount;
		float* min = NULL;
		GLBAccessorType type;

		GLBAccessor(GLBAccessor&) = delete;

		GLBAccessor(char* json);

		static void CallbackConstructor(void* mylocation, char* json);

		static uint64_t GetComponentTypeSize(uint64_t componentType);

		~GLBAccessor();
	};

	enum GLBAnimationChannelTargetPath
	{
		NONE,
		TRANSLATION,
		ROTATION,
		SCALE
	};

	class GLBAnimationChannelTarget
	{
	public:
		uint64_t node;
		GLBAnimationChannelTargetPath path;
		GLBAnimationChannelTarget(GLBAnimationChannelTarget&) = delete;
		GLBAnimationChannelTarget();

		GLBAnimationChannelTarget(char* json);

		~GLBAnimationChannelTarget();
	};

	class GLBAnimationChannel
	{
	public:
		uint64_t sampler;
		GLBAnimationChannelTarget target;
		GLBAnimationChannel(GLBAnimationChannel&) = delete;
		GLBAnimationChannel(char* json);

		static void CallbackConstructor(void* mylocation, char* json);

		~GLBAnimationChannel();
	};

	enum GLBAnimationSamplerInterpolationType
	{
		INTERPOLATION_NONE,
		STEP,
		LINEAR
	};

	class GLBAnimationSampler
	{
	public:
		uint64_t input;
		GLBAnimationSamplerInterpolationType interpolation;
		uint64_t output;
		GLBAnimationSampler(GLBAnimationSampler&) = delete;
		GLBAnimationSampler(char* json);

		static void CallbackConstructor(void* mylocation, char* json);

		~GLBAnimationSampler();
	};

	class GLBAnimation
	{
	public:
		GLBAnimationChannel* channels = NULL;
		uint64_t channelCount;
		char* animationName = NULL;
		GLBAnimationSampler* samplers = NULL;
		uint64_t samplerCount;
		GLBAnimation(GLBAnimation&) = delete;
		GLBAnimation(char* json);

		static void CallbackConstructor(void* mylocation, char* json);

		~GLBAnimation();
	};

	class GLBAsset
	{
	public:
		char* generatorName = NULL;
		char* version = NULL;
		GLBAsset(GLBAsset&) = delete;
		GLBAsset();

		GLBAsset(char* json);

		~GLBAsset();
	};

	class GLBBufferView
	{
	public:
		uint64_t buffer;
		uint64_t byteLength;
		uint64_t byteOffset;
		bool useTarget;
		uint64_t target;
		GLBBufferView(GLBBufferView&) = delete;
		GLBBufferView(char* json);

		static void CallbackConstructor(void* mylocation, char* json);
	};

	class GLBBuffer
	{
	public:
		uint64_t byteLength;
		GLBBuffer(GLBBuffer&) = delete;
		GLBBuffer(char* json);

		static void CallbackConstructor(void* mylocation, char* json);

		~GLBBuffer();
	};

	class GLBImage
	{
	public:
		int bufferView;
		char* name;
		char* mimeType;

		GLBImage(char* json);

		static void CallbackConstructor(void* mylocation, char* json);

		~GLBImage();
	};

	class GLBTexture
	{
	public:
		int sampler;
		int source;

		GLBTexture(char* json);

		static void CallbackConstructor(void* mylocation, char* json);

		~GLBTexture();
	};

	class GLBNormalTexture
	{
	public:
		int index;
	};

	class GLBBaseColorTexture
	{
	public:
		int index;
	};

	class GLBMetallicRoughness
	{
	public:
		float roughnessFactor;
		float metallicFactor;
		GLBBaseColorTexture baseColorTexture;
		GLBMetallicRoughness();
		GLBMetallicRoughness(char* json);

		static void CallbackConstructor(void* mylocation, char* json);

		~GLBMetallicRoughness();
	};

	class GLBMaterial
	{
	public:
		bool doubleSided;
		char* name;
		GLBNormalTexture normalTexture;
		bool normalTextureUsed;
		GLBMetallicRoughness pbrMetallicRoughness;
		bool metallicRoughnessUsed = false;

		GLBMaterial(char* json);

		static void CallbackConstructor(void* mylocation, char* json);

		~GLBMaterial();
	};

	class GLBMeshPrimitive
	{
	public:
		uint64_t indices;
		uint64_t material;
		bool hasMaterial = false;
		PointerList* attributes = NULL;
		uint64_t* values = NULL;
		GLBMeshPrimitive(GLBMeshPrimitive&) = delete;
		GLBMeshPrimitive(char* json);

		static void CallbackConstructor(void* mylocation, char* json);

		~GLBMeshPrimitive();
	};

	class GLBMesh
	{
	public:
		char* name = NULL;
		GLBMeshPrimitive* primitives = NULL;
		uint64_t primitiveCount;
		GLBMesh(GLBMesh&) = delete;
		GLBMesh(char* json);

		static void CallbackConstructor(void* mylocation, char* json);

		~GLBMesh();
	};

	class GLBNode
	{
	public:
		uint64_t* children = NULL;
		uint64_t childrenCount;
		char* name = NULL;
		float* rotation = NULL;
		uint64_t rotationCount;
		float* scale = NULL;
		uint64_t scaleCount;
		float* translation = NULL;
		uint64_t translationCount;
		bool hasMesh = false;
		uint64_t mesh;
		bool hasSkin = false;
		uint64_t skin;


		DirectX::XMMATRIX worldMatrix;
		bool translationOverride = false;
		bool rotationOverride = false;
		bool scaleOverride = false;
		float translationO[3];
		float rotationO[4];
		float scaleO[3];

		GLBNode(GLBNode&) = delete;
		GLBNode(char* json);

		static void CallbackConstructor(void* mylocation, char* json);

		~GLBNode();
	};

	class GLBScene
	{
	public:
		char* name = NULL;
		uint64_t* nodes = NULL;
		uint64_t nodeCount;
		GLBScene(GLBScene&) = delete;
		GLBScene(char* json);

		static void CallbackConstructor(void* mylocation, char* json);

		~GLBScene();
	};

	class GLBSkin
	{
	public:
		uint64_t inverseBindMatrices;
		uint64_t* joints = NULL;
		uint64_t jointCount;
		char* name = NULL;
		GLBSkin(GLBSkin&) = delete;
		GLBSkin(char* json);

		static void CallbackConstructor(void* mylocation, char* json);

		~GLBSkin();
	};

	class GLB
	{
	public:
		DBuffer* binaryData = NULL;

		GLBAccessor* accessors = NULL;
		uint64_t accessorCount;

		GLBAnimation* animations = NULL;
		uint64_t animationCount;

		GLBAsset* asset;

		GLBBufferView* bufferViews = NULL;
		uint64_t bufferViewCount;

		GLBBuffer* buffers = NULL;
		uint64_t bufferCount;

		GLBMesh* meshes = NULL;
		uint64_t meshCount;

		GLBNode* nodes = NULL;
		uint64_t nodeCount;

		uint64_t scene;

		GLBScene* scenes = NULL;
		uint64_t sceneCount;

		GLBSkin* skins = NULL;
		uint64_t skinCount;

		GLBMaterial* materials = NULL;
		uint64_t materialCount;

		GLBTexture* textures = NULL;
		uint64_t textureCount;

		GLBImage* images = NULL;
		uint64_t imageCount;

		GLB(GLB&) = delete;

		GLB(DBuffer* json, DBuffer* bindata);

		static GLB* GetGLB(char* filename);

		~GLB();
	};

	class GLBTreeNode
	{
	public:
		uint64_t index;
		GLBTreeNode* children;
		GLBNode* myself;

		void SetupChildren(GLB* glb, int64_t* mesh, int64_t* skin, uint64_t* count);

		void CalculateWorldMatrix(GLB* glb, DirectX::XMMATRIX parentMatrix);

		~GLBTreeNode();
	};

	GLBTreeNode* SetupNodeTree(GLB* glb, uint64_t rootNodeIndex, int64_t* mesh, int64_t* skin, uint64_t* count);

	GLBTreeNode* GetNodeTree(GLB* glb);
}
