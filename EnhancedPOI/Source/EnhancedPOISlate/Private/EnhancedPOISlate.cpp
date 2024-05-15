
#include "EnhancedPOISlate.h"

#define LOCTEXT_NAMESPACE "FEnhancedPOISlateModule"
void EnhancedPOISlate::StartupModule()
{
	IModuleInterface::StartupModule();
}

void EnhancedPOISlate::ShutdownModule()
{
	IModuleInterface::ShutdownModule();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(EnhancedPOISlate, EnhancedPOISlate)
