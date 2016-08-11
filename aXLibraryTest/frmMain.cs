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
        Ax _aX = null;
        /*Dictionary<String, AXInstance> _instances;
        AXInstance _currentInstance = null;
        AXVariable _currentVariable = null;
        int _currentArrayIndex = -1;
        bool _nodeLoading = false;*/

        AxInstance _instance = null;

        public frmMain()
        {
            InitializeComponent();

            try
            {
                pInstance.Visible = false;
                pVariable.Visible = false;

                _aX = new Ax(20);
                _aX.CycleTime = 1;
                _aX.ShuttingDown += _aX_ShuttingDown;
                //_aX.SpsIdChanged += _aX_OnSpsIdChanged;

                _instance = new AxInstance(_aX, "HomeGear");
                _instance["testvar"].Events = true;
                _instance.VariableValueChanged += _instance_VariableValueChanged;
                _instance["testvarArray"].Events = true;
                _instance.ArrayValueChanged += _instance_ArrayValueChanged;
                //_instance.Dispose();
            }
            catch(Exception ex)
            {
                MessageBox.Show(this, ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                Environment.Exit(1);
            }
        }

        void _instance_VariableValueChanged(AxVariable sender)
        {
            WriteLog(sender.Path + " " + sender.GetString());
        }

        void _instance_ArrayValueChanged(AxVariable sender, UInt16 index)
        {
            WriteLog(sender.Path + " " + index.ToString() + " " + sender.GetString(index));
        }
        
        void _aX_ShuttingDown(Ax sender)
        {
            Environment.Exit(0);
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

        private void frmMain_Load(object sender, EventArgs e)
        {
            
        }

        private void frmMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            _aX.Dispose();
        }

        /*private String GetValueString(AXVariable variable, int index)
        {
            String value = "";
            switch (variable.Type)
            {
                case AXVariableType.axAlarm:
                    value = (index == -1) ? variable.GetBool().ToString() : variable.GetBool((UInt16)index).ToString();
                    break;
                case AXVariableType.axBool:
                    value = (index == -1) ? variable.GetBool().ToString() : variable.GetBool((UInt16)index).ToString();
                    break;
                case AXVariableType.axByte:
                    value = (index == -1) ? variable.GetByte().ToString() : variable.GetByte((UInt16)index).ToString();
                    break;
                case AXVariableType.axInteger:
                    value = (index == -1) ? variable.GetInteger().ToString() : variable.GetInteger((UInt16)index).ToString();
                    break;
                case AXVariableType.axLongInteger:
                    value = (index == -1) ? variable.GetLongInteger().ToString() : variable.GetLongInteger((UInt16)index).ToString();
                    break;
                case AXVariableType.axLongReal:
                    value = (index == -1) ? variable.GetLongReal().ToString() : variable.GetLongReal((UInt16)index).ToString();
                    break;
                case AXVariableType.axReal:
                    value = (index == -1) ? variable.GetReal().ToString() : variable.GetReal((UInt16)index).ToString();
                    break;
                case AXVariableType.axShortInteger:
                    value = (index == -1) ? variable.GetShortInteger().ToString() : variable.GetShortInteger((UInt16)index).ToString();
                    break;
                case AXVariableType.axString:
                    value = (index == -1) ? variable.GetString() : variable.GetString((UInt16)index);
                    break;
                case AXVariableType.axUnsignedInteger:
                    value = (index == -1) ? variable.GetUnsignedInteger().ToString() : variable.GetUnsignedInteger((UInt16)index).ToString();
                    break;
                case AXVariableType.axUnsignedLongInteger:
                    value = (index == -1) ? variable.GetUnsignedLongInteger().ToString() : variable.GetUnsignedLongInteger((UInt16)index).ToString();
                    break;
                case AXVariableType.axUnsignedShortInteger:
                    value = (index == -1) ? variable.GetByte().ToString() : variable.GetByte((UInt16)index).ToString();
                    break;
            }
            return value;
        }*/

        private void tvInstances_AfterSelect(object sender, TreeViewEventArgs e)
        {
            /*if (e.Node == null) return;
            _nodeLoading = true;
            if (e.Node.Level == 0)
            {
                _currentInstance = _instances[e.Node.Text];
                txtInstanceName.Text = _currentInstance.Name;
                txtInstanceRemark.Text = _currentInstance.Remark;
                txtStatus.Text = _currentInstance.Status;
                txtError.Text = _currentInstance.Error;
                chkError.Checked = _currentInstance.Get(txtAlarmVariableName.Text).GetBool();
                txtPollingInterval.Text = _currentInstance.PollingInterval.ToString();
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
                chkIOVar.Checked = _currentVariable.IO;
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
                catch(Exception) {}
                txtDeclaration.Text = _currentVariable.Declaration.ToString();
                txtDecimalPoints.Text = _currentVariable.DecimalPoints.ToString();
                pInstance.Visible = false;
                pVariable.Visible = true;
            }
            _nodeLoading = false;*/
        }

        private void txtVariableValue_TextChanged(object sender, EventArgs e)
        {
            /*if (_currentInstance == null || _currentVariable == null || _nodeLoading) return;
            bool boolValue = false;
            Int64 integerValue = 0;
            Double realValue = 0;
            try
            {
                switch (_currentVariable.Type)
                {
                    case AXVariableType.axAlarm:
                        if (bool.TryParse(txtVariableValue.Text, out boolValue))
                        {
                            if (_currentArrayIndex == -1) _currentVariable.Set(boolValue); else _currentVariable.Set((UInt16)_currentArrayIndex, boolValue);
                        }
                        break;
                    case AXVariableType.axBool:
                        if (bool.TryParse(txtVariableValue.Text, out boolValue))
                        {
                            if (_currentArrayIndex == -1) _currentVariable.Set(boolValue); else _currentVariable.Set((UInt16)_currentArrayIndex, boolValue);
                        }
                        break;
                    case AXVariableType.axByte:
                        if (Int64.TryParse(txtVariableValue.Text, out integerValue))
                        {
                            if (_currentArrayIndex == -1) _currentVariable.Set((Byte)integerValue); else _currentVariable.Set((UInt16)_currentArrayIndex, (Byte)integerValue);
                        }
                        break;
                    case AXVariableType.axInteger:
                        if (Int64.TryParse(txtVariableValue.Text, out integerValue))
                        {
                            if (_currentArrayIndex == -1) _currentVariable.Set((Int16)integerValue); else _currentVariable.Set((UInt16)_currentArrayIndex, (Int16)integerValue);
                        }
                        break;
                    case AXVariableType.axLongInteger:
                        if (Int64.TryParse(txtVariableValue.Text, out integerValue))
                        {
                            if (_currentArrayIndex == -1) _currentVariable.Set((Int32)integerValue); else _currentVariable.Set((UInt16)_currentArrayIndex, (Int32)integerValue);
                        }
                        break;
                    case AXVariableType.axLongReal:
                        if (Double.TryParse(txtVariableValue.Text, out realValue))
                        {
                            if (_currentArrayIndex == -1) _currentVariable.Set(realValue); else _currentVariable.Set((UInt16)_currentArrayIndex, realValue);
                        }
                        break;
                    case AXVariableType.axReal:
                        if (Double.TryParse(txtVariableValue.Text, out realValue))
                        {
                            if (_currentArrayIndex == -1) _currentVariable.Set((Single)realValue); else _currentVariable.Set((UInt16)_currentArrayIndex, (Single)realValue);
                        }
                        break;
                    case AXVariableType.axShortInteger:
                        if (Int64.TryParse(txtVariableValue.Text, out integerValue))
                        {
                            if (_currentArrayIndex == -1) _currentVariable.Set((sbyte)integerValue); else _currentVariable.Set((UInt16)_currentArrayIndex, (sbyte)integerValue);
                        }
                        break;
                    case AXVariableType.axString:
                        if (_currentArrayIndex == -1) _currentVariable.Set(txtVariableValue.Text); else _currentVariable.Set((UInt16)_currentArrayIndex, txtVariableValue.Text);
                        break;
                    case AXVariableType.axUnsignedInteger:
                        if (Int64.TryParse(txtVariableValue.Text, out integerValue))
                        {
                            if (_currentArrayIndex == -1) _currentVariable.Set((UInt16)integerValue); else _currentVariable.Set((UInt16)_currentArrayIndex, (UInt16)integerValue);
                        }
                        break;
                    case AXVariableType.axUnsignedLongInteger:
                        if (Int64.TryParse(txtVariableValue.Text, out integerValue))
                        {
                            if (_currentArrayIndex == -1) _currentVariable.Set((UInt32)integerValue); else _currentVariable.Set((UInt16)_currentArrayIndex, (UInt32)integerValue);
                        }
                        break;
                    case AXVariableType.axUnsignedShortInteger:
                        if (Int64.TryParse(txtVariableValue.Text, out integerValue))
                        {
                            if (_currentArrayIndex == -1) _currentVariable.Set((Byte)integerValue); else _currentVariable.Set((UInt16)_currentArrayIndex, (Byte)integerValue);
                        }
                        break;
                }
            }
            catch(AXException ex)
            {
                WriteLog("Error changing value of variable " + _currentVariable.Name + " and instance " + _currentInstance.Name + ": " + ex.Message);
            }*/
        }

        private void txtPollingInterval_TextChanged(object sender, EventArgs e)
        {
            UInt32 cycleTime = 100;
            UInt32.TryParse(txtCycleTime.Text, out cycleTime);
            _aX.CycleTime = cycleTime;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            _instance["testvarArray"].Set(2, (_instance["testvarArray"].GetString(2) + "a aklsdfkjlhadsflkajhsdflk asdfölkaj aldksfjöalsdkjf ölakdsjf öalkjdf aölskdjf öalksjdf aölskjdf aölskjdf aölskdjf aölskdjf aösldkjf öalskdjf öalskdjf öalskdjf aölksdjf aölskdj fölasdkjf öalskdjf aölskjdf öalskdjf aöslkdjf öalskdjf öasldkjf aöslkdjf aösldkjf asödlkjf asödlkjf aöslkdjf aöslkdjf asölkdjf asölkdjf aöslkdjf öalskdjf aöslkdjf öaslkdjf asölkdjf öalskdjf aösdlkjfasölkdjf asölkdjf aöslkdjf asölkdjf öalskdjf aöslkdjf aösldkjf aösldkj fasöldkjf alsökjdf aölskdjf öalskdjaslödkj fölaskdjf öalskdjf aölsdkjf sdfölkajs dfölkajsd fölaksjdf öalkdsjf a aksjdfl aksdhfakl sjdflkjahsd lkjahsd flkjasdfl kjashdf lkasjdhf lkajshdf lkasjdhflk asdjhfalskdjhf aslkjdhf laksjdhf laksdjhf aslkdjhf aslkdjhf asldkjhf askljdhf askljdhf aslkdjhf askldjhf askldjhf asldkjhf asdkljhf askljdhf askljdhf asdlkjhf aslkdjhf alksdjhf laksjdhf laskdjhf laksjdhfklasjdhf kalsjdhf öalsdkjf öalsdkjf aösldkfj aösldkjf öalskdjf aösldkfj asödlkfj aölskdfj aölsdklkjasdölf kasdölkfj asödlkjf öaslkdjf öaslkdjf öalsdkjf ölaskdj föalksdjf ölaskdj fölaksjd fölkasdj fölkasdj fölaksjdf ölasdkjf öaslkdjf ölaskdjf fj"));
            _instance["testvarArray"].Set(3, (_instance["testvarArray"].GetString(3) + "a"));
            _instance["testvarArray"].Set(4, (_instance["testvarArray"].GetString(4) + "a"));
        }

        private void tableLayoutPanel1_Paint(object sender, PaintEventArgs e)
        {

        }
    }
}
