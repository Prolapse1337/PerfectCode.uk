#pragma once

#include "Vector.h"
#include "VMatrix.h"
#include "Cheat Main.h"
#include "VF Manager.h"

#define squigglyBracketOpen {
#define squigglyBracketClose }

typedef void* (*CreateInterfaceFn)(const char* pName, int* pReturnCode);

class CGlobalVarsBase;
class IBaseClientDLL;
class ICollideable;
class CBaseHandle;
class IHandleEntity;
class RecvProp;
class RecvTable;
class IPanel;
class ClientClass;
class IClientNetworkable;
class IClientRenderable;
class IClientThinkable;
class IClientEntity;
class C_BaseEntity;
class CViewSetup;
class IClientMode;
class IClientUnknown;

class CGlobalVarsBase
	squigglyBracketOpen
public:
	float     realtime;
	int       framecount;
	float     absoluteframetime;
	float     absoluteframestarttimestddev;
	float     curtime;
	float     frametime;
	int       maxClients;
	int       tickcount;
	float     intervalPerTick;
	float     interpolationAmount;
	int       simTicksThisFrame;
	int       networkProtocol;
	void*     pSaveData;
	bool      bClient;
	bool      bRemoteClient;

private:
	int       nTimestampNetworkingBase;
	int       nTimestampRandomizeWindow;
	squigglyBracketClose;

	class IBaseClientDLL
		squigglyBracketOpen
public:
	virtual int              Connect(CreateInterfaceFn appSystemFactory, CGlobalVarsBase* pGlobals) = 0;
	virtual int              Disconnect(void) = 0;
	virtual int              Init(CreateInterfaceFn appSystemFactory, CGlobalVarsBase* pGlobals) = 0;
	virtual void             PostInit() = 0;
	virtual void             Shutdown(void) = 0;
	virtual void             LevelInitPreEntity(char const* pMapName) = 0;
	virtual void             LevelInitPostEntity() = 0;
	virtual void             LevelShutdown(void) = 0;
	virtual ClientClass*     GetAllClasses(void) = 0;
	squigglyBracketClose;

	extern IBaseClientDLL* m_fClientDll;

class ICollideable
	squigglyBracketOpen
public:
	virtual void pad0();
	virtual const Vector& OBBMins() const;
	virtual const Vector& OBBMaxs() const;
	squigglyBracketClose;

class CBaseHandle
	squigglyBracketOpen
	friend class C_BaseEntityList;

public:
	IHandleEntity * Get() const;
	CBaseHandle();
	CBaseHandle(const CBaseHandle& other);
	CBaseHandle(unsigned long value);
	CBaseHandle(int iEntry, int iSerialNumber);
	void Init(int iEntry, int iSerialNumber);
	void Term();
	bool IsValid() const;
	int GetEntryIndex() const;
	int GetSerialNumber() const;
	int ToInt() const;
	bool operator !=(const CBaseHandle& other) const;
	bool operator ==(const CBaseHandle& other) const;
	bool operator ==(const IHandleEntity* pEnt) const;
	bool operator !=(const IHandleEntity* pEnt) const;
	bool operator <(const CBaseHandle& other) const;
	bool operator <(const IHandleEntity* pEnt) const;
	const CBaseHandle& operator=(const IHandleEntity* pEntity);
	const CBaseHandle& Set(const IHandleEntity* pEntity);

protected:
	unsigned long  m_Index;
	squigglyBracketClose;

class IHandleEntity
	squigglyBracketOpen
public:
	virtual ~IHandleEntity() {}
	virtual void SetRefEHandle(const CBaseHandle& handle) = 0;
	virtual const CBaseHandle& GetRefEHandle() const = 0;
	squigglyBracketClose;

	class bf_read;
	class bf_write;
	typedef unsigned char uint8;
	typedef unsigned short ClientShadowHandle_t;
	typedef unsigned short ClientRenderHandle_t;
	typedef unsigned short ModelInstanceHandle_t;

struct RenderableInstance_t
	squigglyBracketOpen
	uint8 m_nAlpha;
squigglyBracketClose;

struct model_t
	squigglyBracketOpen
	void*      fnHandle;
	char       szName[260];
	__int32    nLoadFlags;
	__int32    nServerCount;
	__int32    type;
	__int32    flags;
	Vector     vecMins;
	Vector     vecMaxs;
	float      radius;
	char       pad[0x1C];
	squigglyBracketClose;

enum class EClassIds : int
	squigglyBracketOpen
	CAI_BaseNPC = 0,
	CAK47,
	CBaseAnimating,
	CBaseAnimatingOverlay,
	CBaseAttributableItem,
	CBaseButton,
	CBaseCombatCharacter,
	CBaseCombatWeapon,
	CBaseCSGrenade,
	CBaseCSGrenadeProjectile,
	CBaseDoor,
	CBaseEntity,
	CBaseFlex,
	CBaseGrenade,
	CBaseParticleEntity,
	CBasePlayer,
	CBasePropDoor,
	CBaseTeamObjectiveResource,
	CBaseTempEntity,
	CBaseToggle,
	CBaseTrigger,
	CBaseViewModel,
	CBaseVPhysicsTrigger,
	CBaseWeaponWorldModel,
	CBeam,
	CBeamSpotlight,
	CBoneFollower,
	CBreakableProp,
	CBreakableSurface,
	CC4,
	CCascadeLight,
	CChicken,
	CColorCorrection,
	CColorCorrectionVolume,
	CCSGameRulesProxy,
	CCSPlayer,
	CCSPlayerResource,
	CCSRagdoll,
	CCSTeam,
	CDEagle,
	CDecoyGrenade,
	CDecoyProjectile,
	CDynamicLight,
	CDynamicProp,
	CEconEntity,
	CEconWearable,
	CEmbers,
	CEntityDissolve,
	CEntityFlame,
	CEntityFreezing,
	CEntityParticleTrail,
	CEnvAmbientLight,
	CEnvDetailController,
	CEnvDOFController,
	CEnvParticleScript,
	CEnvProjectedTexture,
	CEnvQuadraticBeam,
	CEnvScreenEffect,
	CEnvScreenOverlay,
	CEnvTonemapController,
	CEnvWind,
	CFEPlayerDecal,
	CFireCrackerBlast,
	CFireSmoke,
	CFireTrail,
	CFish,
	CFlashbang,
	CFogController,
	CFootstepControl,
	CFunc_Dust,
	CFunc_LOD,
	CFuncAreaPortalWindow,
	CFuncBrush,
	CFuncConveyor,
	CFuncLadder,
	CFuncMonitor,
	CFuncMoveLinear,
	CFuncOccluder,
	CFuncReflectiveGlass,
	CFuncRotating,
	CFuncSmokeVolume,
	CFuncTrackTrain,
	CGameRulesProxy,
	CHandleTest,
	CHEGrenade,
	CHostage,
	CHostageCarriableProp,
	CIncendiaryGrenade,
	CInferno,
	CInfoLadderDismount,
	CInfoOverlayAccessor,
	CItem_Healthshot,
	CItemDogtags,
	CKnife,
	CKnifeGG,
	CLightGlow,
	CMaterialModifyControl,
	CMolotovGrenade,
	CMolotovProjectile,
	CMovieDisplay,
	CParticleFire,
	CParticlePerformanceMonitor,
	CParticleSystem,
	CPhysBox,
	CPhysBoxMultiplayer,
	CPhysicsProp,
	CPhysicsPropMultiplayer,
	CPhysMagnet,
	CPlantedC4,
	CPlasma,
	CPlayerResource,
	CPointCamera,
	CPointCommentaryNode,
	CPointWorldText,
	CPoseController,
	CPostProcessController,
	CPrecipitation,
	CPrecipitationBlocker,
	CPredictedViewModel,
	CProp_Hallucination,
	CPropDoorRotating,
	CPropJeep,
	CPropVehicleDriveable,
	CRagdollManager,
	CRagdollProp,
	CRagdollPropAttached,
	CRopeKeyframe,
	CSCAR17,
	CSceneEntity,
	CSensorGrenade,
	CSensorGrenadeProjectile,
	CShadowControl,
	CSlideshowDisplay,
	CSmokeGrenade,
	CSmokeGrenadeProjectile,
	CSmokeStack,
	CSpatialEntity,
	CSpotlightEnd,
	CSprite,
	CSpriteOriented,
	CSpriteTrail,
	CStatueProp,
	CSteamJet,
	CSun,
	CSunlightShadowControl,
	CTeam,
	CTeamplayRoundBasedRulesProxy,
	CTEArmorRicochet,
	CTEBaseBeam,
	CTEBeamEntPoint,
	CTEBeamEnts,
	CTEBeamFollow,
	CTEBeamLaser,
	CTEBeamPoints,
	CTEBeamRing,
	CTEBeamRingPoint,
	CTEBeamSpline,
	CTEBloodSprite,
	CTEBloodStream,
	CTEBreakModel,
	CTEBSPDecal,
	CTEBubbles,
	CTEBubbleTrail,
	CTEClientProjectile,
	CTEDecal,
	CTEDust,
	CTEDynamicLight,
	CTEEffectDispatch,
	CTEEnergySplash,
	CTEExplosion,
	CTEFireBullets,
	CTEFizz,
	CTEFootprintDecal,
	CTEFoundryHelpers,
	CTEGaussExplosion,
	CTEGlowSprite,
	CTEImpact,
	CTEKillPlayerAttachments,
	CTELargeFunnel,
	CTEMetalSparks,
	CTEMuzzleFlash,
	CTEParticleSystem,
	CTEPhysicsProp,
	CTEPlantBomb,
	CTEPlayerAnimEvent,
	CTEPlayerDecal,
	CTEProjectedDecal,
	CTERadioIcon,
	CTEShatterSurface,
	CTEShowLine,
	CTesla,
	CTESmoke,
	CTESparks,
	CTESprite,
	CTESpriteSpray,
	CTest_ProxyToggle_Networkable,
	CTestTraceline,
	CTEWorldDecal,
	CTriggerPlayerMovement,
	CTriggerSoundOperator,
	CVGuiScreen,
	CVoteController,
	CWaterBullet,
	CWaterLODControl,
	CWeaponAug,
	CWeaponAWP,
	CWeaponBaseItem,
	CWeaponBizon,
	CWeaponCSBase,
	CWeaponCSBaseGun,
	CWeaponCycler,
	CWeaponElite,
	CWeaponFamas,
	CWeaponFiveSeven,
	CWeaponG3SG1,
	CWeaponGalil,
	CWeaponGalilAR,
	CWeaponGlock,
	CWeaponHKP2000,
	CWeaponM249,
	CWeaponM3,
	CWeaponM4A1,
	CWeaponMAC10,
	CWeaponMag7,
	CWeaponMP5Navy,
	CWeaponMP7,
	CWeaponMP9,
	CWeaponNegev,
	CWeaponNOVA,
	CWeaponP228,
	CWeaponP250,
	CWeaponP90,
	CWeaponSawedoff,
	CWeaponSCAR20,
	CWeaponScout,
	CWeaponSG550,
	CWeaponSG552,
	CWeaponSG556,
	CWeaponSSG08,
	CWeaponTaser,
	CWeaponTec9,
	CWeaponTMP,
	CWeaponUMP45,
	CWeaponUSP,
	CWeaponXM1014,
	CWorld,
	DustTrail,
	MovieExplosion,
	ParticleSmokeGrenade,
	RocketTrail,
	SmokeTrail,
	SporeExplosion,
	SporeTrail
		squigglyBracketClose;

typedef enum
squigglyBracketOpen
	DPT_Int = 0,
	DPT_Float,
	DPT_Vector,
	DPT_VectorXY,
	DPT_String,
	DPT_Array,
	DPT_DataTable,
#if 0
	DPT_Quaternion,
#endif
	DPT_NUMSendPropTypes
	squigglyBracketClose

SendPropType;

class RecvProp;
class DVariant;
class RecvTable;
class CRecvProxyData;
typedef void(*RecvVarProxyFn)(const CRecvProxyData* pData, void* pStruct, void* pOut);
typedef void(*ArrayLengthRecvProxyFn)(void* pStruct, int objectID, int currentArrayLength);
typedef void(*DataTableRecvVarProxyFn)(const RecvProp* pProp, void** pOut, void* pData, int objectID);

class RecvProp
	squigglyBracketOpen
public:
	RecvProp();

	void                        InitArray(int nElements, int elementStride);
	int                         GetNumElements() const;
	void                        SetNumElements(int nElements);
	int                         GetElementStride() const;
	void                        SetElementStride(int stride);
	int                         GetFlags() const;
	const char*                 GetName() const;
	SendPropType                GetType() const;
	RecvTable*                  GetDataTable() const;
	void                        SetDataTable(RecvTable* pTable);
	RecvVarProxyFn              GetProxyFn() const;
	void                        SetProxyFn(RecvVarProxyFn fn);
	DataTableRecvVarProxyFn     GetDataTableProxyFn() const;
	void                        SetDataTableProxyFn(DataTableRecvVarProxyFn fn);
	int                         GetOffset() const;
	void                        SetOffset(int o);
	RecvProp*                   GetArrayProp() const;
	void                        SetArrayProp(RecvProp* pProp);
	void                        SetArrayLengthProxy(ArrayLengthRecvProxyFn proxy);
	ArrayLengthRecvProxyFn      GetArrayLengthProxy() const;
	bool                        IsInsideArray() const;
	void                        SetInsideArray();
	const void*                 GetExtraData() const;
	void                        SetExtraData(const void* pData);
	const char*                 GetParentArrayPropName();
	void                        SetParentArrayPropName(const char* pArrayPropName);

public:
	const char*                 pVarName;
	SendPropType                RecvType;
	int                         Flags;
	int                         StringBufferSize;

public:
	bool                        bInsideArray;
	const void*                 pExtraData;
	RecvProp*                   pArrayProp;
	ArrayLengthRecvProxyFn      ArrayLengthProxy;
	RecvVarProxyFn              ProxyFn;
	DataTableRecvVarProxyFn     DataTableProxyFn;
	RecvTable*                  pDataTable;
	int                         Offset;
	int                         ElementStride;
	int                         nElements;
	const char*                 pParentArrayPropName;
	squigglyBracketClose;

class CRecvDecoder;

class RecvTable
	squigglyBracketOpen
public:
	typedef RecvProp PropType;
	RecvTable();
	RecvTable(RecvProp* pProps, int nProps, const char* pNetTableName);
	~RecvTable();

	void                Construct(RecvProp* pProps, int nProps, const char* pNetTableName);
	int                 GetNumProps();
	RecvProp*           GetProp(int i);
	const char*         GetName();
	void                SetInitialized(bool bInitialized);
	bool                IsInitialized() const;
	void                SetInMainList(bool bInList);
	bool                IsInMainList() const;

public:
	RecvProp * pProps;
	int                 nProps;
	CRecvDecoder*       pDecoder;
	const char*         pNetTableName;

private:
	bool                bInitialized;
	bool                bInMainList;
	squigglyBracketClose;

inline int RecvTable::GetNumProps()
squigglyBracketOpen
	return this->nProps;
	squigglyBracketClose

inline RecvProp* RecvTable::GetProp(int i)
squigglyBracketOpen
	return &this->pProps[i];
	squigglyBracketClose

inline const char* RecvTable::GetName()
squigglyBracketOpen
	return this->pNetTableName;
	squigglyBracketClose

inline void RecvTable::SetInitialized(bool bInitialized)
squigglyBracketOpen
	this->bInitialized = bInitialized;
	squigglyBracketClose

inline bool RecvTable::IsInitialized() const
squigglyBracketOpen
	return this->bInitialized;
	squigglyBracketClose

inline void RecvTable::SetInMainList(bool bInList)
squigglyBracketOpen
	this->bInMainList = bInList;
	squigglyBracketClose

inline bool RecvTable::IsInMainList() const
squigglyBracketOpen
	return this->bInMainList;
	squigglyBracketClose

inline void RecvProp::InitArray(int nElements, int elementStride)
squigglyBracketOpen
	this->RecvType = DPT_Array;
	this->nElements = nElements;
	this->ElementStride = elementStride;
	squigglyBracketClose

inline int RecvProp::GetNumElements() const
squigglyBracketOpen
	return this->nElements;
	squigglyBracketClose

inline void RecvProp::SetNumElements(int nElements)
squigglyBracketOpen
	this->nElements = nElements;
	squigglyBracketClose

inline int RecvProp::GetElementStride() const
squigglyBracketOpen
	return this->ElementStride;
	squigglyBracketClose

inline void RecvProp::SetElementStride(int stride)
squigglyBracketOpen
	this->ElementStride = stride;
	squigglyBracketClose

inline int RecvProp::GetFlags() const
squigglyBracketOpen
	return this->Flags;
	squigglyBracketClose

inline const char* RecvProp::GetName() const
squigglyBracketOpen
	return this->pVarName;
	squigglyBracketClose

inline SendPropType RecvProp::GetType() const
squigglyBracketOpen
	return this->RecvType;
	squigglyBracketClose

inline RecvTable* RecvProp::GetDataTable() const
squigglyBracketOpen
	return this->pDataTable;
	squigglyBracketClose

inline void RecvProp::SetDataTable(RecvTable* pTable)
squigglyBracketOpen
	this->pDataTable = pTable;
	squigglyBracketClose

inline RecvVarProxyFn RecvProp::GetProxyFn() const
squigglyBracketOpen
	return this->ProxyFn;
	squigglyBracketClose

inline void RecvProp::SetProxyFn(RecvVarProxyFn fn)
squigglyBracketOpen
	this->ProxyFn = fn;
	squigglyBracketClose

inline DataTableRecvVarProxyFn RecvProp::GetDataTableProxyFn() const
squigglyBracketOpen
	return this->DataTableProxyFn;
	squigglyBracketClose

inline void RecvProp::SetDataTableProxyFn(DataTableRecvVarProxyFn fn)
squigglyBracketOpen
	this->DataTableProxyFn = fn;
	squigglyBracketClose

inline int RecvProp::GetOffset() const
squigglyBracketOpen
	return this->Offset;
	squigglyBracketClose

inline void RecvProp::SetOffset(int o)
squigglyBracketOpen
	this->Offset = o;
	squigglyBracketClose

inline RecvProp* RecvProp::GetArrayProp() const
squigglyBracketOpen
	return this->pArrayProp;
	squigglyBracketClose

inline void RecvProp::SetArrayProp(RecvProp* pProp)
squigglyBracketOpen
	this->pArrayProp = pProp;
	squigglyBracketClose

inline void RecvProp::SetArrayLengthProxy(ArrayLengthRecvProxyFn proxy)
squigglyBracketOpen
	this->ArrayLengthProxy = proxy;
	squigglyBracketClose

inline ArrayLengthRecvProxyFn RecvProp::GetArrayLengthProxy() const
squigglyBracketOpen
	return this->ArrayLengthProxy;
	squigglyBracketClose

inline bool RecvProp::IsInsideArray() const
squigglyBracketOpen
	return this->bInsideArray;
	squigglyBracketClose

inline void RecvProp::SetInsideArray()
squigglyBracketOpen
	this->bInsideArray = true;
	squigglyBracketClose

inline const void* RecvProp::GetExtraData() const
squigglyBracketOpen
	return this->pExtraData;
	squigglyBracketClose

inline void RecvProp::SetExtraData(const void* pData)
squigglyBracketOpen
	this->pExtraData = pData;
	squigglyBracketClose

inline const char* RecvProp::GetParentArrayPropName()
squigglyBracketOpen
	return this->pParentArrayPropName;
	squigglyBracketClose

inline void RecvProp::SetParentArrayPropName(const char* pArrayPropName)
squigglyBracketOpen
	this->pParentArrayPropName = pArrayPropName;
	squigglyBracketClose

		class IClientAlphaProperty;

	class IClientUnknown : public IHandleEntity
		squigglyBracketOpen
		public:
			virtual ICollideable*              GetCollideable() = 0;
			virtual IClientNetworkable*        GetClientNetworkable() = 0;
			virtual IClientRenderable*         GetClientRenderable() = 0;
			virtual IClientEntity*             GetIClientEntity() = 0;
			virtual C_BaseEntity*              GetBaseEntity() = 0;
			virtual IClientThinkable*          GetClientThinkable() = 0;
			virtual IClientAlphaProperty*      GetClientAlphaProperty() = 0;
			squigglyBracketClose;

class ClientClass
	squigglyBracketOpen
	typedef IClientNetworkable* (*CreateEventFn)();
	typedef IClientNetworkable* (*CreateClientClassFn)(int entnum, int serialNum);

public:
	CreateClientClassFn      pCreateFn;
	CreateEventFn            pCreateEventFn;
	char*                    pNetworkName;
	RecvTable*               pRecvTable;
	ClientClass*             pNext;
	EClassIds                ClassID;
	squigglyBracketClose;

class IPanel
	squigglyBracketOpen
public:
	const char* GetName(unsigned int vguiPanel)
		squigglyBracketOpen
		typedef const char *(__thiscall* tGetName)(void*, unsigned int);
	return GetFunction<tGetName>(this, 36)(this, vguiPanel);
	squigglyBracketClose

#ifdef GetClassName
#undef GetClassName
#endif

#ifdef squigglyyyy
#undef squigglyyyy
#endif

		void SetMouseInputEnabled(unsigned int iPanel, bool bState)
		squigglyBracketOpen
		return (GetFunction<void(__thiscall *)(PVOID, int, bool)>(this, 32))(this, iPanel, bState);
	squigglyBracketClose

		const char* GetClassName(unsigned int vguiPanel)
		squigglyBracketOpen
		typedef const char *(__thiscall* tGetClassName)(void*, unsigned int);
	return GetFunction<tGetClassName>(this, 37)(this, vguiPanel);
	squigglyBracketClose
		squigglyBracketClose;

	extern IPanel* m_fPanel;

class IClientNetworkable
	squigglyBracketOpen
public:
	virtual IClientUnknown*  GetIClientUnknown() = 0;
	virtual void             Release() = 0;
	virtual ClientClass*     GetClientClass() = 0;
	virtual void             NotifyShouldTransmit(int state) = 0;
	virtual void             OnPreDataChanged(int updateType) = 0;
	virtual void             OnDataChanged(int updateType) = 0;
	virtual void             PreDataUpdate(int updateType) = 0;
	virtual void             PostDataUpdate(int updateType) = 0;
	virtual void             __unkn(void) = 0;
	virtual bool             IsDormant(void) = 0;
	virtual int              EntIndex(void) const = 0;
	virtual void             ReceiveMessage(int classID, bf_read& msg) = 0;
	virtual void*            GetDataTableBasePtr() = 0;
	virtual void             SetDestroyedOnRecreateEntities(void) = 0;
	squigglyBracketClose;

	class IClientRenderable		
		squigglyBracketOpen
public:
	virtual IClientUnknown*            GetIClientUnknown() = 0;
	virtual Vector const&              GetRenderOrigin(void) = 0;
	virtual QAngle const&              GetRenderAngles(void) = 0;
	virtual bool                       ShouldDraw(void) = 0;
	virtual int                        GetRenderFlags(void) = 0;
	virtual void                       Unused(void) const {}
	virtual ClientShadowHandle_t       GetShadowHandle() const = 0;
	virtual ClientRenderHandle_t&      RenderHandle() = 0;
	virtual model_t*                   GetModel() const = 0;
	virtual int                        DrawModel(int flags, const RenderableInstance_t& instance) = 0;
	virtual int                        GetBody() = 0;
	virtual void                       GetColorModulation(float* color) = 0;
	virtual bool                       LODTest() = 0;
	virtual bool                       SetupBones(matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) = 0;
	virtual void                       SetupWeights(const matrix3x4_t* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights, float* pFlexDelayedWeights) = 0;
	virtual void                       DoAnimationEvents(void) = 0;
	virtual void*                      GetPVSNotifyInterface() = 0;
	virtual void                       GetRenderBounds(Vector& mins, Vector& maxs) = 0;
	virtual void                       GetRenderBoundsWorldspace(Vector& mins, Vector& maxs) = 0;
	virtual void                       GetShadowRenderBounds(Vector& mins, Vector& maxs, int shadowType) = 0;
	virtual bool                       ShouldReceiveProjectedTextures(int flags) = 0;
	virtual bool                       GetShadowCastDistance(float* pDist, int shadowType) const = 0;
	virtual bool                       GetShadowCastDirection(Vector* pDirection, int shadowType) const = 0;
	virtual bool                       IsShadowDirty() = 0;
	virtual void                       MarkShadowDirty(bool bDirty) = 0;
	virtual IClientRenderable*         GetShadowParent() = 0;
	virtual IClientRenderable*         FirstShadowChild() = 0;
	virtual IClientRenderable*         NextShadowPeer() = 0;
	virtual int                        ShadowCastType() = 0;
	virtual void                       CreateModelInstance() = 0;
	virtual ModelInstanceHandle_t      GetModelInstance() = 0;
	virtual const matrix3x4_t&         RenderableToWorldTransform() = 0;
	virtual int                        LookupAttachment(const char* pAttachmentName) = 0;
	virtual   bool                     GetAttachment(int number, Vector& origin, QAngle& angles) = 0;
	virtual bool                       GetAttachment(int number, matrix3x4_t& matrix) = 0;
	virtual float*                     GetRenderClipPlane(void) = 0;
	virtual int                        GetSkin() = 0;
	virtual void                       OnThreadedDrawSetup() = 0;
	virtual bool                       UsesFlexDelayedWeights() = 0;
	virtual void                       RecordToolMessage() = 0;
	virtual bool                       ShouldDrawForSplitScreenUser(int nSlot) = 0;
	virtual uint8                      OverrideAlphaModulation(uint8 nAlpha) = 0;
	virtual uint8                      OverrideShadowAlphaModulation(uint8 nAlpha) = 0;
	squigglyBracketClose;

	class CClientThinkHandlePtr;
	typedef CClientThinkHandlePtr* ClientThinkHandle_t;

	class IClientThinkable
		squigglyBracketOpen
	public:
		virtual IClientUnknown*		GetIClientUnknown() = 0;
		virtual void				ClientThink() = 0;
		virtual ClientThinkHandle_t	GetThinkHandle() = 0;
		virtual void				SetThinkHandle(ClientThinkHandle_t hThink) = 0;
		virtual void				Release() = 0;
		squigglyBracketClose;

	struct SpatializationInfo_t;

	class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
		squigglyBracketOpen
	public:
		virtual void             Release(void) = 0;
		virtual const Vector     GetAbsOrigin(void) const = 0;
		virtual const QAngle     GetAbsAngles(void) const = 0;
		virtual void*            GetMouth(void) = 0;
		virtual bool             GetSoundSpatialization(SpatializationInfo_t info) = 0;
		virtual bool             IsBlurred(void) = 0;
		squigglyBracketClose;

	class C_BaseEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable
		squigglyBracketOpen
private:
	template<class T>
	T GetValue(const int offset)
		squigglyBracketOpen
		return *reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(this) + offset);
	squigglyBracketClose

		template <typename T>
	__forceinline T Member(void* base, DWORD offset = 0)
		squigglyBracketOpen
		return (T)((DWORD)base + offset);
	squigglyBracketClose

public:

	squigglyBracketClose;

	enum class ClearFlags_t
		squigglyBracketOpen
		VIEW_CLEAR_COLOR = 0x1,
		VIEW_CLEAR_DEPTH = 0x2,
		VIEW_CLEAR_FULL_TARGET = 0x4,
		VIEW_NO_DRAW = 0x8,
		VIEW_CLEAR_OBEY_STENCIL = 0x10,
		VIEW_CLEAR_STENCIL = 0x20,
		squigglyBracketClose;;

	enum class MotionBlurMode_t
		squigglyBracketOpen
		MOTION_BLUR_DISABLE = 1,
		MOTION_BLUR_GAME = 2,
		MOTION_BLUR_SFM = 3
		squigglyBracketClose;

	class CViewSetup
		squigglyBracketOpen
public:
	int			x, x_old;
	int			y, y_old;
	int			width, width_old;
	int			height, height_old;
	bool		m_bOrtho;
	float		m_OrthoLeft;
	float		m_OrthoTop;
	float		m_OrthoRight;
	float		m_OrthoBottom;
	bool		m_bCustomViewMatrix;
	matrix3x4_t	m_matCustomViewMatrix;
	char		pad_0x68[0x48];
	float		fov;
	float		fovViewmodel;
	Vector		origin;
	QAngle		angles;
	float		zNear;
	float		zFar;
	float		zNearViewmodel;
	float		zFarViewmodel;
	float		m_flAspectRatio;
	float		m_flNearBlurDepth;
	float		m_flNearFocusDepth;
	float		m_flFarFocusDepth;
	float		m_flFarBlurDepth;
	float		m_flNearBlurRadius;
	float		m_flFarBlurRadius;
	int			m_nDoFQuality;
	int			m_nMotionBlurMode;
	float		m_flShutterTime;
	Vector		m_vShutterOpenPosition;
	QAngle		m_shutterOpenAngles;
	Vector		m_vShutterClosePosition;
	QAngle		m_shutterCloseAngles;
	float		m_flOffCenterTop;
	float		m_flOffCenterBottom;
	float		m_flOffCenterLeft;
	float		m_flOffCenterRight;
	int			m_EdgeBlur;
	squigglyBracketClose;

	class IClientMode
		squigglyBracketOpen
public:
	virtual             ~IClientMode() squigglyBracketOpen squigglyBracketClose
		virtual int         ClientModeCSNormal(void*) = 0;
	virtual void        Init() = 0;
	virtual void        InitViewport() = 0;
	virtual void        Shutdown() = 0;
	virtual void        Enable() = 0;
	virtual void        Disable() = 0;
	virtual void        Layout() = 0;
	virtual IPanel*     GetViewport() = 0;
	virtual void*       GetViewportAnimationController() = 0;
	virtual void        ProcessInput(bool bActive) = 0;
	virtual bool        ShouldDrawDetailObjects() = 0;
	virtual bool        ShouldDrawEntity(C_BaseEntity* pEnt) = 0;
	virtual bool        ShouldDrawLocalPlayer(C_BaseEntity* pPlayer) = 0;
	virtual bool        ShouldDrawParticles() = 0;
	virtual bool        ShouldDrawFog(void) = 0;
	virtual void        OverrideView(CViewSetup* pSetup) = 0;
	virtual int         KeyInput(int down, int keynum, const char* pszCurrentBinding) = 0;
	virtual void        StartMessageMode(int iMessageModeType) = 0;
	virtual IPanel*     GetMessagePanel() = 0;
	virtual void        OverrideMouseInput(float* x, float* y) = 0;
	virtual bool        CreateMove(float flSampleFrametime, void* pCmd) = 0;
	virtual void        LevelInit(const char* newmap) = 0;
	virtual void        LevelShutdown(void) = 0;
	squigglyBracketClose;

	extern IClientMode* m_fClientMode;