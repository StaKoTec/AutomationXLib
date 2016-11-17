using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using AutomationX;

namespace aXLibraryTest
{
    public partial class frmMain : Form
    {
        delegate void SetTextCallback(string text);
        delegate void NoParameterCallback();
        Ax _aX = null;
        Dictionary<String, AxInstance> _instances;
        AxInstance _currentInstance = null;
        AxVariable _currentVariable = null;
        int _currentArrayIndex = -1;
        bool _nodeLoading = false;

        public frmMain()
        {
            InitializeComponent();

            try
            {
                pInstance.Visible = false;
                pVariable.Visible = false;

                _aX = new Ax(20);
                _aX.OnError += _aX_OnError;
                _aX.ShuttingDown += _aX_OnShutdown;
                _aX.SpsIdChangedBefore += _aX_SpsIdChangedBefore;
                _aX.SpsIdChangedAfter += _aX_OnSpsIdChangedAfter;
            }
            catch (Exception ex)
            {
                MessageBox.Show(this, ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                Environment.Exit(1);
            }
        }

        void _aX_OnError(Ax sender, uint errorId, string errorMessage)
        {
            WriteLog("Error: " + errorMessage);
        }

        void _aX_SpsIdChangedBefore(Ax sender)
        {
            WriteLog("SPS ID is changing.");
        }

        void _aX_OnSpsIdChangedAfter(Ax sender)
        {
            WriteLog("SPS ID has changed.");
            List<KeyValuePair<String, AxInstance>> instancesToRemove = new List<KeyValuePair<String, AxInstance>>();
            List<KeyValuePair<String, AxInstance>> instancesToReload = new List<KeyValuePair<String, AxInstance>>();
            foreach(KeyValuePair<String, AxInstance> pair in _instances)
            {
                if (pair.Value.CleanUp) instancesToRemove.Add(pair);
                else if (pair.Value.ReloadRequired) instancesToReload.Add(pair);
            }
            foreach (KeyValuePair<String, AxInstance> instance in instancesToRemove)
            {
                instance.Value.Dispose();
                _instances.Remove(instance.Key);
            }
            foreach (KeyValuePair<String, AxInstance> instance in instancesToReload)
            {
                instance.Value.Dispose();
                _instances.Remove(instance.Key);
                AxInstance newInstance = new AxInstance(_aX, instance.Key);
                _instances.Add(instance.Key, newInstance);
                newInstance.VariableValueChanged += variable_OnValueChanged;
                newInstance.ArrayValueChanged += variable_OnArrayValueChanged;

                AxVariable[] variables = newInstance.Variables;
                foreach (AxVariable variable in variables)
                {
                    variable.Events = true;
                }

                AxInstance[] subinstances = newInstance.Subinstances;
                foreach (AxInstance subinstance in subinstances)
                {
                    subinstance.VariableValueChanged += variable_OnValueChanged;
                    subinstance.ArrayValueChanged += variable_OnArrayValueChanged;
                    _instances.Add(subinstance.Path, subinstance);
                    variables = subinstance.Variables;
                    foreach (AxVariable variable in variables)
                    {
                        variable.Events = true;
                    }
                }
            }
            updateTreeView();
        }

        void WriteLog(String text)
        {
            if (txtLog.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(WriteLog);
                this.Invoke(d, new object[] { text });
            }
            else
            {
                txtLog.Text += text + "\r\n";
                txtLog.SelectionStart = txtLog.Text.Length;
                txtLog.ScrollToCaret();
            }
        }

        void _aX_OnShutdown(Ax sender)
        {
            Environment.Exit(0);
        }

        private void frmMain_Load(object sender, EventArgs e)
        {

        }

        private void updateTreeView()
        {
            if (tvInstances.InvokeRequired)
            {
                NoParameterCallback d = new NoParameterCallback(updateTreeView);
                this.Invoke(d);
            }
            else
            {
                tvInstances.Nodes.Clear();
                pInstance.Visible = false;
                pVariable.Visible = false;
                tvInstances.BeginUpdate();
                foreach (KeyValuePair<String, AxInstance> pair in _instances)
                {
                    TreeNode node = new TreeNode(pair.Key);
                    AxVariable[] variables = pair.Value.Variables;
                    foreach (AxVariable variable in variables)
                    {
                        TreeNode variableNode = new TreeNode(variable.Name);
                        if (variable.IsArray)
                        {
                            for (int i = 0; i < variable.Length; i++)
                            {
                                variableNode.Nodes.Add(i.ToString());
                            }
                        }
                        node.Nodes.Add(variableNode);
                    }
                    tvInstances.Nodes.Add(node);

                    AxInstance[] subinstances = pair.Value.Subinstances;
                    foreach (AxInstance subinstance in subinstances)
                    {
                        node = new TreeNode(subinstance.Path);
                        variables = subinstance.Variables;
                        foreach (AxVariable variable in variables)
                        {
                            TreeNode variableNode = new TreeNode(variable.Name);
                            if (variable.IsArray)
                            {
                                for (int i = 0; i < variable.Length; i++)
                                {
                                    variableNode.Nodes.Add(i.ToString());
                                }
                            }
                            node.Nodes.Add(variableNode);
                        }
                        tvInstances.Nodes.Add(node);
                    }
                }
                tvInstances.EndUpdate();
            }
        }

        private void bnSetClassName_Click(object sender, EventArgs e)
        {
            if (_instances != null)
            {
                foreach (KeyValuePair<String, AxInstance> instance in _instances)
                {
                    if (instance.Value != null) instance.Value.Dispose();
                }
            }
            if (txtClassName.Text.Length == 0) return;
            _currentInstance = null;
            _currentVariable = null;
            List<String> instanceNames = _aX.GetInstanceNames(txtClassName.Text);
            if (instanceNames.Count == 0) MessageBox.Show(this, "No instances with the specified class name were found.", "No instances", MessageBoxButtons.OK, MessageBoxIcon.Information);
            instanceNames.Sort();
            _instances = new Dictionary<String, AxInstance>();
            foreach (String name in instanceNames)
            {
                AxInstance instance = new AxInstance(_aX, name);
                instance.VariableValueChanged += variable_OnValueChanged;
                instance.ArrayValueChanged += variable_OnArrayValueChanged;
                _instances.Add(name, instance);
                AxVariable[] variables = instance.Variables;
                foreach (AxVariable variable in variables)
                {
                    variable.Events = true;
                }

                AxInstance[] subinstances = instance.Subinstances;
                foreach (AxInstance subinstance in subinstances)
                {
                    subinstance.VariableValueChanged += variable_OnValueChanged;
                    subinstance.ArrayValueChanged += variable_OnArrayValueChanged;
                    _instances.Add(subinstance.Path, subinstance);
                    variables = subinstance.Variables;
                    foreach (AxVariable variable in variables)
                    {
                        variable.Events = true;
                    }
                }
            }
            updateTreeView();
        }

        void instance_OnStatus(AxInstance sender, string statusText)
        {
            MessageBox.Show(this, sender.Name + " says: " + statusText, "Status", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        void instance_OnError(AxInstance sender, string errorText)
        {
            MessageBox.Show(this, sender.Name + " says: " + errorText, "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
        }

        void variable_OnArrayValueChanged(AxVariable sender, ushort index, AxVariableValue value, DateTime timestamp)
        {
            WriteLog("Array element with name \"" + sender.Name + "\" of instance \"" + sender.Instance.Name + "\" with index " + index.ToString() + " changed to: " + GetValueString(value));
        }

        void variable_OnValueChanged(AxVariable sender, AxVariableValue value, DateTime timestamp)
        {
            WriteLog("Variable \"" + sender.Name + "\" of instance \"" + sender.Instance.Name + "\" changed to: " + GetValueString(value));
            if(sender.Name == "systemuptime") sender.Instance["systemuptime1"].Set(value.IntegerValue);
        }

        private String GetValueString(AxVariable variable, int index)
        {
            String value = "";
            switch (variable.Type)
            {
                case AxVariableType.axAlarm:
                    value = (index == -1) ? variable.GetBool().ToString() : variable.GetBool((UInt16)index).ToString();
                    break;
                case AxVariableType.axBool:
                    value = (index == -1) ? variable.GetBool().ToString() : variable.GetBool((UInt16)index).ToString();
                    break;
                case AxVariableType.axByte:
                    value = (index == -1) ? variable.GetByte().ToString() : variable.GetByte((UInt16)index).ToString();
                    break;
                case AxVariableType.axInteger:
                    value = (index == -1) ? variable.GetInteger().ToString() : variable.GetInteger((UInt16)index).ToString();
                    break;
                case AxVariableType.axLongInteger:
                    value = (index == -1) ? variable.GetLongInteger().ToString() : variable.GetLongInteger((UInt16)index).ToString();
                    break;
                case AxVariableType.axLongReal:
                    value = (index == -1) ? variable.GetLongReal().ToString() : variable.GetLongReal((UInt16)index).ToString();
                    break;
                case AxVariableType.axReal:
                    value = (index == -1) ? variable.GetReal().ToString() : variable.GetReal((UInt16)index).ToString();
                    break;
                case AxVariableType.axShortInteger:
                    value = (index == -1) ? variable.GetShortInteger().ToString() : variable.GetShortInteger((UInt16)index).ToString();
                    break;
                case AxVariableType.axString:
                    value = (index == -1) ? variable.GetString() : variable.GetString((UInt16)index);
                    break;
                case AxVariableType.axUnsignedInteger:
                    value = (index == -1) ? variable.GetUnsignedInteger().ToString() : variable.GetUnsignedInteger((UInt16)index).ToString();
                    break;
                case AxVariableType.axUnsignedLongInteger:
                    value = (index == -1) ? variable.GetUnsignedLongInteger().ToString() : variable.GetUnsignedLongInteger((UInt16)index).ToString();
                    break;
                case AxVariableType.axUnsignedShortInteger:
                    value = (index == -1) ? variable.GetByte().ToString() : variable.GetByte((UInt16)index).ToString();
                    break;
            }
            return value;
        }

        private String GetValueString(AxVariableValue value)
        {
            String stringValue = "";
            switch (value.Type)
            {
                case AxVariableType.axAlarm:
                    stringValue = value.BoolValue.ToString();
                    break;
                case AxVariableType.axBool:
                    stringValue = value.BoolValue.ToString();
                    break;
                case AxVariableType.axByte:
                    stringValue = value.ByteValue.ToString();
                    break;
                case AxVariableType.axInteger:
                    stringValue = value.IntegerValue.ToString();
                    break;
                case AxVariableType.axLongInteger:
                    stringValue = value.LongIntegerValue.ToString();
                    break;
                case AxVariableType.axLongReal:
                    stringValue = value.LongRealValue.ToString();
                    break;
                case AxVariableType.axReal:
                    stringValue = value.RealValue.ToString();
                    break;
                case AxVariableType.axShortInteger:
                    stringValue = value.ShortIntegerValue.ToString();
                    break;
                case AxVariableType.axString:
                    stringValue = value.StringValue.ToString();
                    break;
                case AxVariableType.axUnsignedInteger:
                    stringValue = value.UnsignedIntegerValue.ToString();
                    break;
                case AxVariableType.axUnsignedLongInteger:
                    stringValue = value.UnsignedLongIntegerValue.ToString();
                    break;
                case AxVariableType.axUnsignedShortInteger:
                    stringValue = value.UnsignedShortIntegerValue.ToString();
                    break;
            }
            return stringValue;
        }

        private void tvInstances_AfterSelect(object sender, TreeViewEventArgs e)
        {
            if (e.Node == null) return;
            _nodeLoading = true;
            if (e.Node.Level == 0)
            {
                _currentInstance = _instances[e.Node.Text];
                txtInstanceName.Text = _currentInstance.Name;
                txtInstanceRemark.Text = _currentInstance.Remark;
                pVariable.Visible = false;
                pInstance.Visible = true;
            }
            else if (e.Node.Level == 1 || e.Node.Level == 2)
            {
                if (e.Node.Level == 1)
                {
                    _currentInstance = _instances[e.Node.Parent.Text];
                    _currentVariable = _currentInstance.Get(e.Node.Text);
                    _currentArrayIndex = (_currentVariable.IsArray) ? 0 : -1;
                }
                else
                {
                    _currentInstance = _instances[e.Node.Parent.Parent.Text];
                    _currentVariable = _currentInstance.Get(e.Node.Parent.Text);
                    Int32.TryParse(e.Node.Text, out _currentArrayIndex);
                }
                txtInstance.Text = _currentInstance.Name;
                txtName.Text = _currentVariable.Name;
                if (_currentArrayIndex == -1) txtIndex.Text = ""; else txtIndex.Text = _currentArrayIndex.ToString();
                txtVariableType.Text = _currentVariable.Type.ToString();
                txtVariableValue.Text = "";
                if (_currentVariable.Constant || _currentVariable.ConfigurationValue) txtVariableValue.ReadOnly = true; else txtVariableValue.ReadOnly = false;
                txtVariableValue.Text = GetValueString(_currentVariable, _currentArrayIndex);
                chkIOVar.Checked = _currentVariable.Io;
                chkNotConnected.Checked = _currentVariable.NotConnected;
                chkGlobal.Checked = _currentVariable.Global;
                chkTrending.Checked = _currentVariable.Trending;
                chkRetentive.Checked = _currentVariable.Retentive;
                chkConstant.Checked = _currentVariable.Constant;
                chkPrivate.Checked = _currentVariable.Private;
                chkLocal.Checked = _currentVariable.Local;
                chkConfValue.Checked = _currentVariable.ConfigurationValue;
                chkParameter.Checked = _currentVariable.Parameter;
                chkRemote.Checked = _currentVariable.Remote;
                txtRemark.Text = _currentVariable.Remark;
                try
                {
                    txtReferenceName.Text = _currentVariable.ReferenceName;
                }
                catch (Exception) { }
                txtDeclaration.Text = _currentVariable.Declaration.ToString();
                txtDecimalPoints.Text = _currentVariable.DecimalPoints.ToString();
                pInstance.Visible = false;
                pVariable.Visible = true;
            }
            _nodeLoading = false;
        }

        private void txtVariableValue_TextChanged(object sender, EventArgs e)
        {
            if (_currentInstance == null || _currentVariable == null || _nodeLoading) return;
            bool boolValue = false;
            Int64 integerValue = 0;
            Double realValue = 0;
            try
            {
                switch (_currentVariable.Type)
                {
                    case AxVariableType.axAlarm:
                        if (bool.TryParse(txtVariableValue.Text, out boolValue))
                        {
                            if (_currentArrayIndex == -1) _currentVariable.Set(boolValue); else _currentVariable.Set((UInt16)_currentArrayIndex, boolValue);
                        }
                        break;
                    case AxVariableType.axBool:
                        if (bool.TryParse(txtVariableValue.Text, out boolValue))
                        {
                            if (_currentArrayIndex == -1) _currentVariable.Set(boolValue); else _currentVariable.Set((UInt16)_currentArrayIndex, boolValue);
                        }
                        break;
                    case AxVariableType.axByte:
                        if (Int64.TryParse(txtVariableValue.Text, out integerValue))
                        {
                            if (_currentArrayIndex == -1) _currentVariable.Set((Byte)integerValue); else _currentVariable.Set((UInt16)_currentArrayIndex, (Byte)integerValue);
                        }
                        break;
                    case AxVariableType.axInteger:
                        if (Int64.TryParse(txtVariableValue.Text, out integerValue))
                        {
                            if (_currentArrayIndex == -1) _currentVariable.Set((Int16)integerValue); else _currentVariable.Set((UInt16)_currentArrayIndex, (Int16)integerValue);
                        }
                        break;
                    case AxVariableType.axLongInteger:
                        if (Int64.TryParse(txtVariableValue.Text, out integerValue))
                        {
                            if (_currentArrayIndex == -1) _currentVariable.Set((Int32)integerValue); else _currentVariable.Set((UInt16)_currentArrayIndex, (Int32)integerValue);
                        }
                        break;
                    case AxVariableType.axLongReal:
                        if (Double.TryParse(txtVariableValue.Text, out realValue))
                        {
                            if (_currentArrayIndex == -1) _currentVariable.Set(realValue); else _currentVariable.Set((UInt16)_currentArrayIndex, realValue);
                        }
                        break;
                    case AxVariableType.axReal:
                        if (Double.TryParse(txtVariableValue.Text, out realValue))
                        {
                            if (_currentArrayIndex == -1) _currentVariable.Set((Single)realValue); else _currentVariable.Set((UInt16)_currentArrayIndex, (Single)realValue);
                        }
                        break;
                    case AxVariableType.axShortInteger:
                        if (Int64.TryParse(txtVariableValue.Text, out integerValue))
                        {
                            if (_currentArrayIndex == -1) _currentVariable.Set((sbyte)integerValue); else _currentVariable.Set((UInt16)_currentArrayIndex, (sbyte)integerValue);
                        }
                        break;
                    case AxVariableType.axString:
                        if (_currentArrayIndex == -1) _currentVariable.Set(txtVariableValue.Text); else _currentVariable.Set((UInt16)_currentArrayIndex, txtVariableValue.Text);
                        break;
                    case AxVariableType.axUnsignedInteger:
                        if (Int64.TryParse(txtVariableValue.Text, out integerValue))
                        {
                            if (_currentArrayIndex == -1) _currentVariable.Set((UInt16)integerValue); else _currentVariable.Set((UInt16)_currentArrayIndex, (UInt16)integerValue);
                        }
                        break;
                    case AxVariableType.axUnsignedLongInteger:
                        if (Int64.TryParse(txtVariableValue.Text, out integerValue))
                        {
                            if (_currentArrayIndex == -1) _currentVariable.Set((UInt32)integerValue); else _currentVariable.Set((UInt16)_currentArrayIndex, (UInt32)integerValue);
                        }
                        break;
                    case AxVariableType.axUnsignedShortInteger:
                        if (Int64.TryParse(txtVariableValue.Text, out integerValue))
                        {
                            if (_currentArrayIndex == -1) _currentVariable.Set((Byte)integerValue); else _currentVariable.Set((UInt16)_currentArrayIndex, (Byte)integerValue);
                        }
                        break;
                }
            }
            catch (AxException ex)
            {
                WriteLog("Error changing value of variable " + _currentVariable.Name + " and instance " + _currentInstance.Name + ": " + ex.Message);
            }
        }

        private void txtInstanceRemark_TextChanged(object sender, EventArgs e)
        {
            if (_currentInstance == null || _nodeLoading) return;
            //_currentInstance.Remark = txtInstanceRemark.Text;
        }

        private void txtRemark_TextChanged(object sender, EventArgs e)
        {
            if (_currentInstance == null || _currentVariable == null || _nodeLoading) return;
            //_currentVariable.Remark = txtRemark.Text;
        }

        private void txtCycleTime_TextChanged(object sender, EventArgs e)
        {
            UInt32 interval = 1;
            UInt32.TryParse(txtCycleTime.Text, out interval);
            _aX.CycleTime = interval;
        }

        private void frmMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            _aX.Dispose();
        }
    }
}
