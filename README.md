# AutomationXLib

This is a .NET library for AutomationX 4.

## Requirements

* AutomationX Version 4.8
* Microsoft .NET-Framework 4.5
* Microsoft Visual C++ Redistributable Packages for Visual Studio 2013 (x86)

## Small C# usage example

First add AutomationX.dll as reference to your project.

### Create a new AutomationX object

```
AutomationX.AX aX = new AutomationX.AX();
aX.ShuttingDown += aX_OnShutdown;
```

### Create one or more new instance objects
```
AutomationX.AXInstance aXInstance1 = new AXInstance(_aX, "MyFirstInstance", "Status", "err");
aXInstance1.StatusEvent += aXInstance_OnStatus;
aXInstance1.ErrorEvent += aXInstance_OnError;
AutomationX.AXInstance aXInstance2 = new AXInstance(_aX, "MySecondInstance", "Status", "err");
aXInstance2.StatusEvent += aXInstance_OnStatus;
aXInstance2.ErrorEvent += aXInstance_OnError;
```

### Enable variable events for instance and add event handler to variable
```
void EnableVariableEvents()
{
	aXInstance1.VariableEvents = true;
	aXInstance1.Get("STATE").ValueChanged += OnValueChanged;
	aXInstance1.Get("MY_ARRAY").ArrayValueChanged += OnArrayValueChanged;
	//To add an event handler for all variables of the instance, you can do:
	//aXInstance1.VariableValueChanged += OnValueChanged;
	//aXInstance1.ArrayValueChanged += OnArrayValueChanged;
}

void OnArrayValueChanged(AXVariable sender, ushort index)
{
	if(sender.Type == AXVariableType.axInteger)
	{
		MessageBox.Show
		(
			"Instance: " + sender.Instance.Name + "\r\n" + 
			"Name: " + sender.Name + "\r\n" + 
			"Index: " + index.ToString() + "\r\n" +
			"Value: " + sender.GetInteger(index).ToString()
		);
	}
}

void OnValueChanged(AXVariable sender)
{
	if (sender.Type == AXVariableType.axBool)
	{
		MessageBox.Show
		(
			"Instance: " + sender.Instance.Name + "\r\n" +
			"Name: " + sender.Name + "\r\n" +
			"Value: " + sender.GetBool().ToString()
		);
	}
}
```

### Write an aX variable
```
AutomationX.AXVariable aXVar1 = axInstance2.Get("STATE");
aXVar1.Set(true);
```

### Read an aX variable

```
aXVar1.GetBool();
```