AutomationXLib
==============

This is a .NET library for AutomationX 4.

Small C# usage example
-------------------

First add AutomationX.dll as reference to your project.

### Create a new AutomationX object

```
AutomationX.AX aX = new AutomationX.AX();
aX.OnShutdown += aX_OnShutdown;
```

### Create one or more new instance objects
```
AutomationX.AXInstance aXInstance1 = new AXInstance(_aX, "MyFirstInstance", "Status", "err");
aXInstance1.OnStatus += aXInstance_OnStatus;
aXInstance1.OnError += aXInstance_OnError;
AutomationX.AXInstance aXInstance2 = new AXInstance(_aX, "MySecondInstance", "Status", "err");
aXInstance2.OnStatus += aXInstance_OnStatus;
aXInstance2.OnError += aXInstance_OnError;
```

### Enable variable events for instance and add event handler to variable
```
void EnableVariableEvents()
{
	aXInstance1.EnableVariableEvents();
	aXInstance1.Get("STATE").OnValueChanged += OnValueChanged;
	aXInstance1.Get("MY_ARRAY").OnArrayValueChanged += OnArrayValueChanged;
}

private void OnArrayValueChanged(AXVariable sender, ushort index)
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