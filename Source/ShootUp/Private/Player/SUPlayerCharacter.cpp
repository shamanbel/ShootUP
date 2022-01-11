// The numbers lead a dance

#include "Player/SUPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SUWeaponComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

ASUPlayerCharacter::ASUPlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{

    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);  //Камера выставлена правее

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
    CameraCollisionComponent->SetupAttachment(CameraComponent);
    CameraCollisionComponent->SetSphereRadius(10.0f);
    CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

void ASUPlayerCharacter::BeginPlay() 
{
    Super::BeginPlay();
    check(CameraCollisionComponent);
    if (!GetWorld()) return;
    CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASUPlayerCharacter::OnCameraCollisionBeginOverlap);
    CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ASUPlayerCharacter::OnCameraCollisionEndOverlap);
}
// Called to bind functionality to input
void ASUPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(WeaponComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ASUPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASUPlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ASUPlayerCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ASUPlayerCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASUPlayerCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASUPlayerCharacter::StartRuning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ASUPlayerCharacter::StopRuning);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &USUWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USUWeaponComponent::StopFire);
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USUWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USUWeaponComponent::Reload);
    
    DECLARE_DELEGATE_OneParam(FZoomInputSignature, bool)
    PlayerInputComponent->BindAction <FZoomInputSignature>("Zoom", IE_Pressed, WeaponComponent, &USUWeaponComponent::Zoom, true);
    PlayerInputComponent->BindAction<FZoomInputSignature>("Zoom", IE_Released, WeaponComponent, &USUWeaponComponent::Zoom, false);
}
void ASUPlayerCharacter::MoveForward(float Amount)
{
    IsMovingForward = Amount > 0.0f;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ASUPlayerCharacter::MoveRight(float Amount)
{
    AddMovementInput(GetActorRightVector(), Amount);
}

void ASUPlayerCharacter::StartRuning()
{
    HaveToRun = true;
}

void ASUPlayerCharacter::StopRuning()
{
    HaveToRun = false;
}
void ASUPlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    CheckCameraOverlap();
}
void ASUPlayerCharacter::OnCameraCollisionEndOverlap(
    UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    CheckCameraOverlap();
}
void ASUPlayerCharacter::CheckCameraOverlap() 
{
    const bool HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
    GetMesh()->SetOwnerNoSee(HideMesh);

    TArray<USceneComponent*> MeshChildren;
    GetMesh()->GetChildrenComponents(true, MeshChildren);
    for (auto MeshChild : MeshChildren)
    {
        const auto MeshChildGeometry = Cast<UPrimitiveComponent>(MeshChild);
        if (MeshChildGeometry)
        {
            MeshChildGeometry->SetOwnerNoSee(HideMesh);
        }
    }

}
bool ASUPlayerCharacter::IsRunning() const
{
    return HaveToRun && IsMovingForward && !GetVelocity().IsZero();  //Проверка движения вперед
}

void ASUPlayerCharacter::OnDeath()
{
 
    Super::OnDeath();
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }

}


