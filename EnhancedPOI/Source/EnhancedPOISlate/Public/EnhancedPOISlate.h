
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class EnhancedPOISlate  : public IModuleInterface
{
public:

protected:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	
};
