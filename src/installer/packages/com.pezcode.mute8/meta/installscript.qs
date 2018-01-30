function Component()
{
    // default constructor
}

Component.prototype.createOperations = function()
{
    // call default implementation to install files
    component.createOperations();

    if (systemInfo.productType === "windows") {
        component.addOperation("CreateShortcut", "@TargetDir@/@Name@.exe", "@StartMenuDir@/@Name@.lnk", "description=Open @Name@");
        component.addOperation("CreateShortcut", "@TargetDir@/@MaintenanceToolName@.exe", "@StartMenuDir@/Uninstall @Name@.lnk", "description=Uninstall @Name@");
    }
}
