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
        AX _aX1 = new AutomationX.AX("Tannenbaum", "Status", "err");
        AX _aX2 = new AutomationX.AX("Tannenbaum2", "Status", "err");

        public Form1()
        {
            InitializeComponent();

            _aX1.OnStatus += bla_OnStatus;
            _aX1.OnError += bla_OnError;
            _aX2.OnStatus += bla_OnStatus;
            _aX2.OnError += bla_OnError;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        
        }

        void bla_OnStatus(AX sender, string statusText)
        {
            MessageBox.Show(statusText, sender.GetInstanceName() + " - Status", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        void bla_OnError(AX sender, string errorText)
        {
            MessageBox.Show(errorText, sender.GetInstanceName() + " - Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                AXWriter writer = new AutomationX.AXWriter(_aX1);
                writer.WriteBool("Tannenbaum", "STATE", true);
                AXReader reader = new AutomationX.AXReader(_aX1);
                System.Collections.Generic.List<String> instanceNames = reader.GetInstanceNames("Aktor_1fach");
                button1.Text = reader.GetInstanceRemark("Tannenbaum3") + " " + reader.GetVariableRemark("Tannenbaum", "STATE").ToString();
                _aX1.SetError("Hi!");
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

        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                AXWriter writer = new AutomationX.AXWriter(_aX2);
                writer.WriteInteger("RSSI", -152);
                AXReader reader = new AutomationX.AXReader(_aX2);
                button2.Text = reader.ReadInteger("RSSI").ToString();
                _aX2.SetStatus("Moin!");
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
