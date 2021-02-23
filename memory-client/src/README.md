# Nathans-Tarkov-Radar
Linux Client

## Building
This project uses the meson build system, to build it run `meson` while specifying the build directory as a parameter.
`meson build`
In the build directory run `ninja` to compile, an executable named `TarkovInjector` will be produced.

## Running
To execute the project run it as root providing the WebSocket URL and passcode as two separate parameters, you can provide the optional parameter -s to auto reconnect to the WebSocket on disconnection.
`sudo ./TarkovInjector http://127.0.0.1:8080 boop -s`
`sudo ./TarkovInjector --help`

## Offsets
`
// https://www.unknowncheats.me/forum/escape-from-tarkov/226519-escape-tarkov-reversal-structs-offsets-158.html#post3017333
// Created with ReClass.NET 1.2 by KN4CK3R
 
// Reversed by:  @Respecter
 
GetGOM: 0x156B698
GetGetPosition: 0xC13070
CAMERA: 0x150DA00
 
class EFT.GameWorld // Aka LocalGameWorld
{
public:
	char pad_0000[24]; //0x0000
	class ExitController *m_pExitController; //0x0018
	char pad_0020[16]; //0x0020
	class UnityEngineString *CurrentProfileId; //0x0030
	char pad_0038[40]; //0x0038
	class ArrayItems *m_pItemList; //0x0060 LootList
	char pad_0068[24]; //0x0068
	class Array *RegisteredPlayers; //0x0080
}; //Size: 0x0088
 
class Array
{
public:
	char pad_0000[16]; //0x0000
	class List *m_pList; //0x0010
	int32_t Count; //0x0018
	int32_t MaxCount; //0x001C
}; //Size: 0x0020
 
class List
{
public:
	char pad_0000[32]; //0x0000
	class Player *m_pFirstEntity; //0x0020
	class Player *m_pSecondPlayer; //0x0028
	char pad_0030[64]; //0x0030
}; //Size: 0x0070
 
class Player
{
public:
	char pad_0000[24]; //0x0000
	class LocalPlayerChecker *m_pLocalPlayerChecker; //0x0018
	class CharacterController *m_pCharacterController; //0x0020
	char pad_0028[24]; //0x0028
	class MovementContext *m_pMovementContext; //0x0040
	char pad_0048[96]; //0x0048
	class PlayerBody *m_pPlayerBody; //0x00A8
	char pad_00B0[224]; //0x00B0
	class ProceduralWeaponAnimation *m_pProceduralWeaponAnimation; //0x0190
	char pad_0198[672]; //0x0198
	class PlayerProfile *m_pPlayerProfile; //0x0438
	char pad_0440[40]; //0x0440
	class HealthController *m_pHealthController; //0x0468
}; //Size: 0x0470
 
class MovementContext
{
public:
	char pad_0000[504]; //0x0000
	Vector2 ViewAngles; //0x01F8
	Vector2 ViewAngles2; //0x0200
	Vector3 LocalPosition; //0x0208
}; //Size: 0x0214
 
class CAMERA // Aka FPS Camera
{
public:
	char pad_0000[48]; //0x0000
	class FPSCamera *m_pFpsCamera; //0x0030
}; //Size: 0x0038
 
class FPSCamera
{
public:
	char pad_0000[48]; //0x0000
	class CameraObject *m_pCameraObject; //0x0030
	char pad_0038[40]; //0x0038
	char *ObjectName; //0x0060
}; //Size: 0x0068
 
class CameraObject
{
public:
	char pad_0000[8]; //0x0000
	class CameraContainer *m_pCameraContainer; //0x0008
	char pad_0010[8]; //0x0010
	class CameraEntity *m_pCameraEntity; //0x0018
}; //Size: 0x0020
 
class CameraEntity
{
public:
	char pad_0000[416]; //0x0000
	Matrix4x4 ViewMatrix0; //0x01A0
	Matrix4x4 ViewMatrix; //0x01E0
}; //Size: 0x0220
 
class PlayerBody
{
public:
	char pad_0000[40]; //0x0000
	class m_pSkeletonRootJoin *m_pSkeletonRootJoin; //0x0028
}; //Size: 0x0030
 
class m_pSkeletonRootJoin
{
public:
	char pad_0000[40]; //0x0000
	class BoneEnumerator *m_pBoneEnumerator; //0x0028
}; //Size: 0x0030
 
class BoneEnumerator
{
public:
	char pad_0000[16]; //0x0000
	class TransformArray *m_pTransformArray; //0x0010
}; //Size: 0x0018
 
class TransformArray
{
public:
	char pad_0000[8]; //0x0000
}; //Size: 0x0008
 
class PlayerProfile // EFT.Profile
{
public:
	char pad_0000[16]; //0x0000
	class UnityEngineString *Id; //0x0010 (type: System.String)
	class UnityEngineString *AccountId; //0x0018 (type: System.String)
	class UnityEngineString *PetId; //0x0020 (type: System.String)
	class PlayerInfo *Info; //0x0028
	char pad_0030[16]; //0x0030
	class PlayerHealth *Health; //0x0040
}; //Size: 0x0048
 
class PlayerInfo
{
public:
	char pad_0000[16]; //0x0000
	class UnityEngineString *Nickname; //0x0010 (type: System.String)
	class UnityEngineString *GroupId; //0x0018 (type: System.String)
	class UnityEngineString *EntryPoint; //0x0020 (type: System.String)
	char pad_0028[16]; //0x0028
	class RE_Settings *Settings; //0x0038 re_Settings
	char pad_0040[16]; //0x0040
	int32_t Side; //0x0050 (type: EFT.EPlayerSide)
	int32_t RegistrationDate; //0x0054
	float SavageLockTime; //0x0058
	int32_t NicknameChangeDate; //0x005C
	int32_t MemberCategory; //0x0060 (type: EMemberCategory)
	int32_t Experience; //0x0064 int_0
}; //Size: 0x0068
 
class UnityEngineString // (type: System.String)
{
public:
	char pad_0000[16]; //0x0000
	int32_t size; //0x0010
	wchar_t name[31]; //0x0014
}; //Size: 0x0052
 
class HealthController // _healthController
{
public:
	char pad_0000[32]; //0x0000
	class HealthBody *m_pHealthBody; //0x0020
}; //Size: 0x0028
 
class HealthBody
{
public:
	char pad_0000[24]; //0x0000
	class BodyController *m_pBodyController; //0x0018
	char pad_0020[8]; //0x0020
}; //Size: 0x0028
 
class BodyController
{
public:
	char pad_0000[48]; //0x0000
	class HealthContainer *m_pHealthHead; //0x0030
	char pad_0038[16]; //0x0038
	class HealthContainer *m_pHealthThorax; //0x0048
	char pad_0050[16]; //0x0050
	class HealthContainer *m_pHealthStomach; //0x0060
	char pad_0068[16]; //0x0068
	class HealthContainer *m_pHealthLeftArm; //0x0078
	char pad_0080[16]; //0x0080
	class HealthContainer *m_pHealthRightArm; //0x0090
	char pad_0098[16]; //0x0098
	class HealthContainer *m_pHealthLeftLeg; //0x00A8
	char pad_00B0[16]; //0x00B0
	class HealthContainer *m_pHealthRightLeg; //0x00C0
}; //Size: 0x00C8
 
class HealthContainer
{
public:
	char pad_0000[16]; //0x0000
	class Health *m_pHealth; //0x0010
	char pad_0018[16]; //0x0018
}; //Size: 0x0028
 
class Health
{
public:
	char pad_0000[16]; //0x0000
	float Health; //0x0010
	float HealthMax; //0x0014
}; //Size: 0x0018
 
class PlayerHealth
{
public:
	char pad_0000[24]; //0x0000
	class HealthInfo *m_playerHealthInfo; //0x0018
}; //Size: 0x0020
 
class HealthInfo
{
public:
	char pad_0000[16]; //0x0000
	float CurentHealth; //0x0010
	float MaxHealth; //0x0014
}; //Size: 0x0018
 
class CameraContainer
{
public:
	char pad_0000[56]; //0x0000
	class CameraPosition *m_pCameraPosition; //0x0038
}; //Size: 0x0040
 
class CameraPosition
{
public:
	char pad_0000[176]; //0x0000
	Vector3 cameraPosition; //0x00B0
	char pad_00BC[4]; //0x00BC
	Vector4 cameraRotation; //0x00C0
}; //Size: 0x00D0
 
class ArrayItems
{
public:
	char pad_0000[16]; //0x0000
	class ItemList *m_pItemList; //0x0010
	int32_t Count; //0x0018
	int32_t MaxCout; //0x001C
}; //Size: 0x0020
 
class ItemList
{
public:
	char pad_0000[32]; //0x0000
	class Loot *m_pFirstItem; //0x0020
	class Loot *m_pSecondItem; //0x0028
}; //Size: 0x0030
 
class Loot
{
public:
	char pad_0000[16]; //0x0000
	class ItemProfile *m_pItemProfile; //0x0010
}; //Size: 0x0018
 
class ItemProfile
{
public:
	char pad_0000[40]; //0x0000
	class Interactive *Interactive; //0x0028 EFT.Interactive.etc
	class GameObject *Object; //0x0030
}; //Size: 0x0038
 
class GameObject
{
public:
	char pad_0000[48]; //0x0000
	class TransformOne *m_pTransformOne; //0x0030
	char pad_0038[40]; //0x0038
	char *ObjectName; //0x0060
}; //Size: 0x0068
 
class TransformOne
{
public:
	char pad_0000[8]; //0x0000
	class TransformTwo *TransformTwo; //0x0008
}; //Size: 0x0010
 
class TransformTwo
{
public:
	char pad_0000[56]; //0x0000
	class TransformOk *Transform; //0x0038
}; //Size: 0x0040
 
class TransformOk
{
public:
	char pad_0000[176]; //0x0000
	Vector3 Position; //0x00B0
}; //Size: 0x00BC
 
class ProceduralWeaponAnimation
{
public:
	char pad_0000[24]; //0x0000
	class PlayerSpring *HandsContainer; //0x0018 (type: EFT.Animations.PlayerSpring)
	char pad_0020[8]; //0x0020
	class BreathEffector *Breath; //0x0028 (type: EFT.Animations.BreathEffector)
	class WalkEffector *Walk; //0x0030 (type: WalkEffector)
	class MotionEffector *MotionReact; //0x0038 (type: MotionEffector)
	class ForceEffector *ForceReact; //0x0040 (type: ForceEffector)
	class ShotEffector *Shootingg; //0x0048 (type: ShotEffector)
	class TurnAwayEffector *TurnAway; //0x0050 (type: TurnAwayEffector)
	class CustomEffector *CustomEffector; //0x0058
	char pad_0060[152]; //0x0060
	int32_t Mask; //0x00F8 Write zero for no-recoil / no - sway
	Vector3 Offset; //0x00FC
	char pad_0108[28]; //0x0108
	int32_t AimIndex; //0x0124
	float CameraSmoothTime; //0x0128
	char pad_012C[48]; //0x012C
	bool IsAiming; //0x015C
	bool Sprint; //0x015D
	bool ShouldMoveWeaponCloser; //0x015E
	char pad_015F[1]; //0x015F
	Vector3 VCameraTarget; //0x0160 _vCameraTarget
	Vector3 RotationCameraOffset; //0x016C
	int32_t PointOfView; //0x0178 enum (type: EFT.EPointOfView)
	char pad_017C[28]; //0x017C
	float AimFovDeltaZ; //0x0198
	float float_11; //0x019C
	float float_12; //0x01A0
	float _agsDeltaHeight; //0x01A4
	Vector4 quaternion_2; //0x01A8
	Vector4 quaternion_3; //0x01B8
	float FovScale; //0x01C8
	Vector3 _shotDirection; //0x01CC
	float float_14; //0x01D8
	Vector3 TacticalReloadStiffnes; //0x01DC
	float TacticalReloadPosition; //0x01E8
	float CameraSmoothSteady; //0x01EC
	float CameraSmoothRecoil; //0x01F0
	float CameraSmoothOut; //0x01F4
	Vector3 AimSwayMax; //0x01F8
	Vector3 AimSwayMin; //0x0204
	float SwayFalloff; //0x0210
	char pad_0214[36]; //0x0214
	Vector4 quaternion_4; //0x0238
	Vector4 quaternion_5; //0x0248
	Vector3 vector3_4; //0x0258
	char pad_0264[136]; //0x0264
	float ErgonomicWeight; //0x02EC
	float SWAY_STRENGTH_PER_KG; //0x02F0
	float DISPLACEMENT_STRENGTH_PER_KG; //0x02F4
	char pad_02F8[36]; //0x02F8
	bool TacticalReload; //0x031C
	bool OverlappingAllowsBlindfire; //0x031D
	bool OnScopeMode; //0x031E
	bool ShotNeedsFovAdjustments; //0x031F
}; //Size: 0x0320
 
class Interactive // EFT.Interactive.etc
{
public:
	char pad_0000[80]; //0x0000
	class Item *Item; //0x0050 EFT.InventoryLogic.Item
	char pad_0058[176]; //0x0058
	class RE_ItemOwner *ItemOwner; //0x0108
}; //Size: 0x0110
 
class StatsNames
{
public:
	char pad_0000[32]; //0x0000
	class ItemNames *m_pItemNames; //0x0020
}; //Size: 0x0028
 
class ItemNames
{
public:
	char pad_0000[80]; //0x0000
	class UnityEngineString *m_pItemHashIdentifier; //0x0050
	char pad_0058[8]; //0x0058
	class UnityEngineString *m_pParentHashIdentifier; //0x0060
}; //Size: 0x0068
 
class BreathEffector // (type: EFT.Animations.BreathEffector)
{
public:
	char pad_0000[16]; //0x0000
	class RE_Physical *Physical; //0x0010
	class Spring *HandsRotationSpring; //0x0018
	class Spring *RecoilRotationSpring; //0x0020
	char pad_0028[120]; //0x0028
	bool IsAiming; //0x00A0
	char pad_00A1[3]; //0x00A1
	float Intensity; //0x00A4
	float ShakeIntensity; //0x00A8
	float BreathIntensity; //0x00AC
	float BreathFrequency; //0x00B0
	float HipPenalty; //0x00B4
	bool TremorOn; //0x00B8
	bool Fracture; //0x00B9
	char pad_00BA[2]; //0x00BA
	float CameraSensetivity; //0x00BC
	float IdleUntill; //0x00C0
	float EnergyLowerLimit; //0x00C4
	float EnergyFractureLimit; //0x00C8
	float AmplitudeGainPerShot; //0x00CC
	float Delay; //0x00D0
	Vector2 BaseHipRandomAmplitudes; //0x00D4
	Vector2 RandomBetween; //0x00DC
	float ShotHardness; //0x00E4
	float float_0; //0x00E8
}; //Size: 0x00EC
 
class ShotEffector // (type: ShotEffector)
{
public:
	char pad_0000[40]; //0x0000
	class Weapon *Weapon; //0x0028 (type: EFT.InventoryLogic.Weapon)
	char pad_0030[8]; //0x0030
	Vector2 RecoilStrengthXy; //0x0038
	Vector2 RecoilStrengthZ; //0x0040
	Vector2 RecoilDegree; //0x0048
	Vector3 RecoilDirection; //0x0050
	Vector2 RecoilRadian; //0x005C
	float Stiffness; //0x0064
	float Intensity; //0x0068
	Vector3 XIntensityByPose; //0x006C
	Vector3 YIntensityByPose; //0x0078
	Vector3 ZIntensityByPose; //0x0084
	Vector3 SeparateIntensityFactors; //0x0090
	int32_t Pose; //0x009C 0 - laydown - 1 crounch - 2 stand
}; //Size: 0x00A0
 
class CameraRaw
{
public:
	char pad_0000[48]; //0x0000
	class FPSCamera *m_pCameraEntity; //0x0030
	char pad_0038[1]; //0x0038
	bool IsActive; //0x0039
}; //Size: 0x003A
 
class PlayerId
{
public:
	char pad_0000[16]; //0x0000
	int32_t N000007E4; //0x0010
	wchar_t N000007F5[24]; //0x0014
	char pad_0044[112]; //0x0044
}; //Size: 0x00B4
 
class LocalPlayerChecker
{
public:
	char pad_0000[8]; //0x0000
}; //Size: 0x0008
 
class ExitController
{
public:
	char pad_0000[32]; //0x0000
	class ExfiltrationPointArray *m_pExfiltrationPointArray; //0x0020 exfiltrationPoint_0
	class ExfiltrationPointArray *m_pExfiltrationPointScav; //0x0028 scavExfiltrationPoint_0
}; //Size: 0x0030
 
class ExfiltrationPointArray // (type: EFT.Interactive.ExfiltrationPoint[])
{
public:
	char pad_0000[24]; //0x0000
	int32_t ExFitrationCount; //0x0018
	char pad_001C[4]; //0x001C
	class ExfiltrationPoint *m_pFirstExfiltrationPoint; //0x0020
	class ExfiltrationPoint *m_pSecondExfiltrationPoint; //0x0028
}; //Size: 0x0030
 
class ExfiltrationPoint
{
public:
	char pad_0000[16]; //0x0000
	class PositionStuff *m_pPositionStuff; //0x0010
	char pad_0018[64]; //0x0018
	class Settings *m_pSettings; //0x0058
	char pad_0060[72]; //0x0060
	uint8_t Status; //0x00A8 (type: EFT.Interactive.EExfiltrationStatus
	char pad_00A9[3]; //0x00A9
	float ExfiltrationStartTime; //0x00AC
	bool Reusable; //0x00B0
}; //Size: 0x00B1
 
class Settings // EFT.Interactive.ExitTriggerSettings
{
public:
	char pad_0000[16]; //0x0000
	class UnityEngineString *Name; //0x0010 Name
	class UnityEngineString *EntryPoints; //0x0018
	int32_t ExfiltrationType; //0x0020 (type: EFT.Interactive.EExfiltrationType)
	float ExfiltrationTime; //0x0024
	int32_t PlayersCount; //0x0028
	float Chance; //0x002C
	float MinTime; //0x0030
	float MaxTime; //0x0034
	float StartTime; //0x0038
}; //Size: 0x003C
 
class PositionStuff
{
public:
	char pad_0000[48]; //0x0000
	class PositionStuff2 *m_pPositionStuff2; //0x0030
}; //Size: 0x0038
 
class PositionStuff2
{
public:
	char pad_0000[48]; //0x0000
	class PositionStuff3 *m_pPositionStuff3; //0x0030
}; //Size: 0x0038
 
class PositionStuff3
{
public:
	char pad_0000[8]; //0x0000
	class ExtractionTransforms *m_pExtractionTransform; //0x0008
}; //Size: 0x0010
 
class ExtractionTransforms
{
public:
	char pad_0000[40]; //0x0000
	class ExtranctionTransformPointer *m_pExtractionTransform; //0x0028
}; //Size: 0x0030
 
class ExtranctionTransformPointer
{
public:
	char pad_0000[16]; //0x0000
	class Transform *m_pTransform; //0x0010
}; //Size: 0x0018
 
class Transform
{
public:
	char pad_0000[40]; //0x0000
	Matrix4x4 ExitMatrix; //0x0028
}; //Size: 0x0068
 
class Item // EFT.InventoryLogic.Item
{
public:
	char pad_0000[56]; //0x0000
	class ItemTemplate *m_pItemTemplate; //0x0038
	char pad_0040[40]; //0x0040
	class Grids *Grids; //0x0068
}; //Size: 0x0070
 
class PlayerSpring // (type: EFT.Animations.PlayerSpring)
{
public:
	char pad_0000[24]; //0x0000
	class Spring *HandsPosition; //0x0018 (type: EFT.Animations.Spring)
	class Spring *HandsRotation; //0x0020 (type: EFT.Animations.Spring)
	char pad_0028[8]; //0x0028
	class Spring *CameraRotation; //0x0030 (type: EFT.Animations.Spring)
	class Spring *CameraPosition; //0x0038 (type: EFT.Animations.Spring)
}; //Size: 0x0040
 
class Spring
{
public:
	char pad_0000[40]; //0x0000
	Vector3 Zero; //0x0028
	float InputIntensity; //0x0034
	float ReturnSpeed; //0x0038
	float Damping; //0x003C
	Vector3 Min; //0x0040
	Vector3 Max; //0x004C
	float AccelerationMax; //0x0058
	float CurveTime; //0x005C
	bool Refrash; //0x0060
	char pad_0061[3]; //0x0061
	float Softness; //0x0064
	float X; //0x0068 EFT.Animations.Spring.VecComponent)
	float Y; //0x006C EFT.Animations.Spring.VecComponent)
	float Z; //0x0070 EFT.Animations.Spring.VecComponent)
	Vector3 Velocity; //0x0074
	Vector3 Current; //0x0080
	Vector3 ForceAccumulator; //0x008C
	Vector3 ForceAccumulatorLimitless; //0x0098
	bool Update; //0x00A4
}; //Size: 0x00A5
 
class CharacterController
{
public:
	char pad_0000[216]; //0x0000
	Vector3 Velocity; //0x00D8
}; //Size: 0x00E4
 
class RE_Settings // re_Settings
{
public:
	char pad_0000[16]; //0x0000
	int32_t Role; //0x0010 (type: EFT.WildSpawnType)
	int32_t Level; //0x0014 (type: BotDifficulty)
	int32_t Experience; //0x0018 Do not work
}; //Size: 0x001C
 
class CAMERA_GLOBAL
{
public:
	class CamerasArray *m_pCamerasArray; //0x0000
}; //Size: 0x0008
 
class CamerasArray
{
public:
	class Cameras *m_pCamera; //0x0000
	int64_t Min; //0x0008
	int64_t Count; //0x0010
	int64_t Max; //0x0018
}; //Size: 0x0020
 
class Cameras
{
public:
	class CameraRaw *m_pCameraOne; //0x0000
}; //Size: 0x0008
 
class TurnAwayEffector
{
public:
	char pad_0000[68]; //0x0000
	float BlendSpeed; //0x0044
	float TurnAwayThreshold; //0x0048
	float PlayerOverlapThreshold; //0x004C
	float SmoothTimeIn; //0x0050
	float SmoothTimeOut; //0x0054
	int32_t POV; //0x0058
	bool IsPistol; //0x005C
	bool IsInProne; //0x005D
	bool IsDirty; //0x005E
	char pad_005F[1]; //0x005F
	float FovInput; //0x0060
	bool OverlapsWithPlayer; //0x0064
	char pad_0065[3]; //0x0065
	float OverlapDepth; //0x0068
	float OriginZShift; //0x006C
	float FovScale; //0x0070
	float NormalFovScale; //0x0074
	float Overlap; //0x0078
	float Blend; //0x007C
	Vector3 Position; //0x0080
	Vector3 Rotation; //0x008C
	Vector3 CameraShift; //0x0098
	Vector3 LElbowShift; //0x00A4
	Vector3 RElbowShift; //0x00B0
	float CameraZShift; //0x00BC
	float MaxZShift; //0x00C0
	float CameraShiftAtMaxOverlap; //0x00C4
}; //Size: 0x00C8
 
class RE_Physical
{
public:
	char pad_0000[40]; //0x0000
	class RE_Stamina *Stamina; //0x0028
	class RE_Stamina *HandsStamina; //0x0030
	class RE_Stamina *Oxygen; //0x0038
	char pad_0040[56]; //0x0040
	float MaxPoseLevel; //0x0078
	float Overweight; //0x007C
	float WalkOverweight; //0x0080
	float WalkSpeedLimit; //0x0084
	float SoundRadius; //0x0088
	bool bool_0; //0x008C
	char pad_008D[3]; //0x008D
	float float_2; //0x0090
	float Fatigue; //0x0094
	float CapacityBuff; //0x0098
	float float_3; //0x009C
	float FallDamageMultiplier; //0x00A0
	float StaminaCapacity; //0x00A4
	float StaminaRestoreRate; //0x00A8
	float HandsCapacity; //0x00AC
	float HandsRestoreRate; //0x00B0
	float OxygenCapacity; //0x00B4
	float OxygenRestoreRate; //0x00B8
	Vector2 WalkOverweightLimits; //0x00BC
	Vector2 BaseOverweightLimits; //0x00C4
	Vector2 SprintOverweightLimits; //0x00CC
	Vector2 WalkSpeedOverweightLimits; //0x00D4
	float float_4; //0x00DC
	float PreviousWeight; //0x00E0
	bool bool_1; //0x00E4
	bool bool_2; //0x00E5
	char pad_00E6[3]; //0x00E6
	bool bool_3; //0x00E9
	bool bool_4; //0x00EA
	bool bool_5; //0x00EB
	bool bool_6; //0x00EC
}; //Size: 0x00ED
 
class RE_Stamina
{
public:
	char pad_0000[72]; //0x0000
	float Current; //0x0048
	float DisableRestoration; //0x004C
	float float_0; //0x0050
	bool bool_0; //0x0054
	char pad_0055[3]; //0x0055
	int32_t int_0; //0x0058
}; //Size: 0x005C
 
class WalkEffector
{
public:
	char pad_0000[64]; //0x0000
	float StepFrequency; //0x0040
	float Intensity; //0x0044
	float SideSpeedMultyplyer; //0x0048
	float BackSpeedMultyplyer; //0x004C
	float Treshold; //0x0050
	Vector3 LastPosition; //0x0054
	bool IsWalking; //0x0060
	char pad_0061[3]; //0x0061
	float Overweight; //0x0064
	int32_t CurrentWalkPreset; //0x0068 (type: WalkEffector.EWalkPreset)
	float Speed; //0x006C
}; //Size: 0x0070
 
class MotionEffector
{
public:
	char pad_0000[72]; //0x0000
	Vector3 Motion; //0x0048
	Vector3 Velocity; //0x0054
	float RotationInputClamp; //0x0060
	Vector3 LastPosition; //0x0064
	Vector3 LastForward; //0x0070
	Vector3 PositionVelocity; //0x007C
	Vector2 RotationVelocity; //0x0088
	Vector3 PositionAcceleration; //0x0090
	Vector2 RotationAcceleration; //0x009C
	Vector3 SwayFactors; //0x00A4
	Vector3 LastPositionVelocity; //0x00B0
	Vector2 LastRotationVelocity; //0x00BC
	Vector3 lastRotation; //0x00C4
	float Intensity; //0x00D0
	Vector3 PlatformMovement; //0x00D4
	Vector2 V; //0x00E0
	Vector2 V4; //0x00E8
	bool Initialized; //0x00F0
	char pad_00F1[3]; //0x00F1
	Vector3 V2; //0x00F4
	Vector3 V3; //0x0100
	bool NeedReset; //0x010C
}; //Size: 0x010D
 
class ForceEffector // (type: ForceEffector)
{
public:
	char pad_0000[32]; //0x0000
	class Spring *CameraRotationSpring; //0x0020
	class Spring *HandsRotationSpring; //0x0028
	float Intensity; //0x0030
	bool Initialized; //0x0034
	char pad_0035[3]; //0x0035
	Vector3 Force; //0x0038
	int32_t FramesLeft; //0x0044
	float EulersNoiseXYMaxValue; //0x0048
	float EulersNoiseZMaxValue; //0x004C
	float DeltaRandom; //0x0050
	float WiggleMagnitude; //0x0054
}; //Size: 0x0058
 
class CustomEffector
{
public:
	char pad_0000[56]; //0x0000
	bool Inited; //0x0038
	char pad_0039[3]; //0x0039
	float RestTransitionSpeed; //0x003C
	float RestDelay; //0x0040
	float LastActivityTime; //0x0044
	float InitAimRotation; //0x0048
	float PoseNormalTime; //0x004C
	float AimTarget; //0x0050
}; //Size: 0x0054
 
class Weapon
{
public:
	char pad_0000[24]; //0x0000
	class UnityEngineString *Id; //0x0018
	char pad_0020[16]; //0x0020
	class UnityEngineString *ToStringCache; //0x0030
	char pad_0038[8]; //0x0038
	class ItemTemplate *Template; //0x0040
}; //Size: 0x0048
 
class ItemTemplate
{
public:
	char pad_0000[16]; //0x0000
	class UnityEngineString *Name; //0x0010
	class UnityEngineString *ShortName; //0x0018
	class UnityEngineString *Description; //0x0020
	class UnityEngineString *ItemSound; //0x0028
	char pad_0030[32]; //0x0030
	class UnityEngineString *Id; //0x0050
	class UnityEngineString *_Name; //0x0058
	class UnityEngineString *_Parent; //0x0060
	char pad_0068[32]; //0x0068
	float Weight; //0x0088
	bool ExaminedByDefault; //0x008C
	char pad_008D[3]; //0x008D
	float ExamineTime; //0x0090
	bool QuestItem; //0x0094
	char pad_0095[3]; //0x0095
	int32_t BackgroundColor; //0x0098
	int32_t Width; //0x009C
	int32_t Height; //0x00A0
	char pad_00A4[20]; //0x00A4
	int32_t StackMaxSize; //0x00B8
	int32_t StackObjectsCount; //0x00BC
	int32_t CreditsPrice; //0x00C0
	int32_t Rarity; //0x00C4
	float SpawnChance; //0x00C8
	bool NotShownInSlot; //0x00CC
	char pad_00CD[3]; //0x00CD
	int32_t LootExperience; //0x00D0
	bool HideEntrails; //0x00D4
	char pad_00D5[3]; //0x00D5
	int32_t ExamineExperience; //0x00D8
	int32_t RepairCost; //0x00DC
	int32_t RepairSpeed; //0x00E0
	bool MergesWithChildren; //0x00E4
	bool CanSellOnRagfair; //0x00E5
	bool CanRequireOnRagfair; //0x00E6
	char pad_00E7[1]; //0x00E7
	int32_t AnimationVariantsNumber; //0x00E8
	bool Unlootable; //0x00EC
	char pad_00ED[3]; //0x00ED
	int32_t UnlootableFromSide; //0x00F0
	int32_t _type; //0x00F4
}; //Size: 0x00F8
 
class RE_ItemOwner
{
public:
	char pad_0000[144]; //0x0000
	class Item *Item; //0x0090 EFT.InventoryLogic.Item
}; //Size: 0x0098
 
class Grids
{
public:
	char pad_0000[24]; //0x0000
	int32_t Count; //0x0018
	char pad_001C[4]; //0x001C
	class Grid *Grid; //0x0020
}; //Size: 0x0028
 
class Grid
{
public:
	char pad_0000[64]; //0x0000
	class GridDict *GridDict; //0x0040
}; //Size: 0x0048
 
class GridDict
{
public:
	char pad_0000[16]; //0x0000
	class Dict *Dict; //0x0010
}; //Size: 0x0018
 
class Dict
{
public:
	char pad_0000[24]; //0x0000
	class Entries *Entries; //0x0018
	char pad_0020[32]; //0x0020
	int32_t Count; //0x0040
	int32_t Max; //0x0044
}; //Size: 0x0048
 
class Entries
{
public:
	char pad_0000[40]; //0x0000
	class Item *FirstITem; //0x0028 Entries + 0x28 + 0x18 * i
}; //Size: 0x0030
