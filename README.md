AutomationXLib
==============

This is a .NET library for AutomationX 4.

Small usage example
-------------------

First add AutomationX.dll as reference to your project.

### Then to create a new AutomationX object, do:

> AutomationX.AX aX = new AutomationX.AX("MyInstanceName", "Status", "err");

### Listen for a status, error or shutdown event

> aX.OnStatus += aX_OnStatus;
> aX.OnError += aX_OnError;
> aX.OnShutdown += aX_OnShutdown;

### Write an aX variable
> AutomationX.AXWriter w = new AutomationX.AXWriter(aX);
> w.WriteBool("MyInstanceName", "STATE", true);

### Read an aX variable

> AutomationX.AXReader r = new AutomationX.AXReader(aX);
> r.ReadBool("MyInstanceName", "STATE");