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
    public partial class Form1 : Form
    {
        AX _aX = null;
        AXInstance _aXInstance1 = null;
        AXInstance _aXInstance2 = null;

        public Form1()
        {
            InitializeComponent();

            try
            {
                _aX = new AX();
                _aX.OnShutdown += _aX_OnShutdown;
                _aXInstance1 = new AXInstance(_aX, "Tannenbaum", "Status", "err");
                _aXInstance2 = new AXInstance(_aX, "Tannenbaum2", "Status", "err");
                _aXInstance1.OnStatus += _aXInstance_OnStatus;
                _aXInstance1.OnError += _aXInstance_OnError;
                _aXInstance2.OnStatus += _aXInstance_OnStatus;
                _aXInstance2.OnError += _aXInstance_OnError;
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                Environment.Exit(1);
            }
        }

        void _aXInstance_OnError(AXInstance sender, string errorText)
        {
            MessageBox.Show(sender.Name + " says: " + errorText, "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
        }

        void _aXInstance_OnStatus(AXInstance sender, string statusText)
        {
            MessageBox.Show(sender.Name + " says: " + statusText, "Status", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        void _aX_OnShutdown(AX sender)
        {
            Environment.Exit(0);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                _aXInstance1.EnableVariableEvents();
                _aXInstance1.Get("STATE").OnValueChanged += OnValueChanged;
                _aXInstance1.Get("aint").OnArrayValueChanged += OnArrayValueChanged;
            }
            catch (AXNotRunningException ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
            catch (AXException ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
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

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                MessageBox.Show(_aXInstance1.Get("STATE").GetBool().ToString());
                MessageBox.Show(_aXInstance1.Get("aint").GetInteger(5).ToString());
            }
            catch (AXNotRunningException ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
            catch (AXException ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
            }
        }
    }
}
