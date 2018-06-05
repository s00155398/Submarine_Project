// Fill out your copyright notice in the Description page of Project Settings.
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TurretAimingComponent.generated.h" 
UENUM()
enum class ETurretFiringState : uint8{ Reloading ,Aiming, Locked};
class UTurretBarrel;
class UTurretHead;
class ATorpedo;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SUBMARINEPROJECT_API UTurretAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTurretAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Initialise(UTurretBarrel* BarrelToSet, UTurretHead* TurretToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

	ETurretFiringState GetFiringState() const;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
		ETurretFiringState FiringState = ETurretFiringState::Reloading;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
private:
	void MoveBarrelTowards(FVector AimDirection);

	bool IsBarrelMoving();

	UTurretBarrel* Barrel = nullptr;
	UTurretHead* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<ATorpedo> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSeconds = 3;

	double LastFireTime = 0;

	FVector AimDirection;
};
