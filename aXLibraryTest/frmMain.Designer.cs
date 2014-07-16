namespace aXLibraryTest
{
    partial class frmMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.txtLog = new System.Windows.Forms.TextBox();
            this.txtClassName = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.bnSetClassName = new System.Windows.Forms.Button();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.tvInstances = new System.Windows.Forms.TreeView();
            this.pInstance = new System.Windows.Forms.Panel();
            this.txtInstanceName = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.txtError = new System.Windows.Forms.TextBox();
            this.txtStatus = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.txtInstanceRemark = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.chkError = new System.Windows.Forms.CheckBox();
            this.pVariable = new System.Windows.Forms.Panel();
            this.chkEvents = new System.Windows.Forms.CheckBox();
            this.txtIndex = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.txtName = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.txtInstance = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.txtRemark = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.chkRemote = new System.Windows.Forms.CheckBox();
            this.chkGlobal = new System.Windows.Forms.CheckBox();
            this.chkNotConnected = new System.Windows.Forms.CheckBox();
            this.chkPrivate = new System.Windows.Forms.CheckBox();
            this.chkIOVar = new System.Windows.Forms.CheckBox();
            this.chkConfValue = new System.Windows.Forms.CheckBox();
            this.chkConstant = new System.Windows.Forms.CheckBox();
            this.chkParameter = new System.Windows.Forms.CheckBox();
            this.chkRetentive = new System.Windows.Forms.CheckBox();
            this.chkLocal = new System.Windows.Forms.CheckBox();
            this.chkTrending = new System.Windows.Forms.CheckBox();
            this.txtVariableValue = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.txtVariableType = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.txtStatusVariableName = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.txtAlarmVariableName = new System.Windows.Forms.TextBox();
            this.txtReferenceName = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.txtDeclaration = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.txtDecimalPoints = new System.Windows.Forms.TextBox();
            this.label15 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).BeginInit();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).BeginInit();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            this.pInstance.SuspendLayout();
            this.pVariable.SuspendLayout();
            this.SuspendLayout();
            // 
            // txtLog
            // 
            this.txtLog.Dock = System.Windows.Forms.DockStyle.Fill;
            this.txtLog.Location = new System.Drawing.Point(0, 0);
            this.txtLog.Multiline = true;
            this.txtLog.Name = "txtLog";
            this.txtLog.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtLog.Size = new System.Drawing.Size(835, 121);
            this.txtLog.TabIndex = 2;
            // 
            // txtClassName
            // 
            this.txtClassName.Location = new System.Drawing.Point(79, 6);
            this.txtClassName.Name = "txtClassName";
            this.txtClassName.Size = new System.Drawing.Size(205, 20);
            this.txtClassName.TabIndex = 3;
            this.txtClassName.Text = "Aktor_1fach";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(9, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(66, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "Class Name:";
            // 
            // bnSetClassName
            // 
            this.bnSetClassName.Location = new System.Drawing.Point(764, 6);
            this.bnSetClassName.Name = "bnSetClassName";
            this.bnSetClassName.Size = new System.Drawing.Size(48, 20);
            this.bnSetClassName.TabIndex = 5;
            this.bnSetClassName.Text = "Set";
            this.bnSetClassName.UseVisualStyleBackColor = true;
            this.bnSetClassName.Click += new System.EventHandler(this.bnSetClassName_Click);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.splitContainer1.Location = new System.Drawing.Point(12, 32);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.splitContainer2);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.txtLog);
            this.splitContainer1.Size = new System.Drawing.Size(835, 536);
            this.splitContainer1.SplitterDistance = 411;
            this.splitContainer1.TabIndex = 6;
            // 
            // splitContainer2
            // 
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Name = "splitContainer2";
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.Controls.Add(this.tvInstances);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.pVariable);
            this.splitContainer2.Panel2.Controls.Add(this.pInstance);
            this.splitContainer2.Size = new System.Drawing.Size(835, 411);
            this.splitContainer2.SplitterDistance = 247;
            this.splitContainer2.TabIndex = 0;
            // 
            // tvInstances
            // 
            this.tvInstances.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tvInstances.Location = new System.Drawing.Point(0, 0);
            this.tvInstances.Name = "tvInstances";
            this.tvInstances.Size = new System.Drawing.Size(247, 411);
            this.tvInstances.TabIndex = 0;
            this.tvInstances.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.tvInstances_AfterSelect);
            // 
            // pInstance
            // 
            this.pInstance.Controls.Add(this.txtInstanceName);
            this.pInstance.Controls.Add(this.label12);
            this.pInstance.Controls.Add(this.txtError);
            this.pInstance.Controls.Add(this.txtStatus);
            this.pInstance.Controls.Add(this.label3);
            this.pInstance.Controls.Add(this.txtInstanceRemark);
            this.pInstance.Controls.Add(this.label2);
            this.pInstance.Controls.Add(this.chkError);
            this.pInstance.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pInstance.Location = new System.Drawing.Point(0, 0);
            this.pInstance.Name = "pInstance";
            this.pInstance.Size = new System.Drawing.Size(584, 411);
            this.pInstance.TabIndex = 0;
            // 
            // txtInstanceName
            // 
            this.txtInstanceName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtInstanceName.Location = new System.Drawing.Point(56, 3);
            this.txtInstanceName.Name = "txtInstanceName";
            this.txtInstanceName.ReadOnly = true;
            this.txtInstanceName.Size = new System.Drawing.Size(525, 20);
            this.txtInstanceName.TabIndex = 8;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(3, 6);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(38, 13);
            this.label12.TabIndex = 7;
            this.label12.Text = "Name:";
            // 
            // txtError
            // 
            this.txtError.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtError.Location = new System.Drawing.Point(56, 81);
            this.txtError.Name = "txtError";
            this.txtError.Size = new System.Drawing.Size(525, 20);
            this.txtError.TabIndex = 5;
            // 
            // txtStatus
            // 
            this.txtStatus.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtStatus.Location = new System.Drawing.Point(56, 55);
            this.txtStatus.Name = "txtStatus";
            this.txtStatus.ReadOnly = true;
            this.txtStatus.Size = new System.Drawing.Size(525, 20);
            this.txtStatus.TabIndex = 3;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(3, 58);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(40, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "Status:";
            // 
            // txtInstanceRemark
            // 
            this.txtInstanceRemark.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtInstanceRemark.Location = new System.Drawing.Point(56, 29);
            this.txtInstanceRemark.Name = "txtInstanceRemark";
            this.txtInstanceRemark.ReadOnly = true;
            this.txtInstanceRemark.Size = new System.Drawing.Size(525, 20);
            this.txtInstanceRemark.TabIndex = 1;
            this.txtInstanceRemark.TextChanged += new System.EventHandler(this.txtInstanceRemark_TextChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 32);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(47, 13);
            this.label2.TabIndex = 0;
            this.label2.Text = "Remark:";
            // 
            // chkError
            // 
            this.chkError.AutoSize = true;
            this.chkError.Location = new System.Drawing.Point(6, 83);
            this.chkError.Name = "chkError";
            this.chkError.Size = new System.Drawing.Size(51, 17);
            this.chkError.TabIndex = 6;
            this.chkError.Text = "Error:";
            this.chkError.UseVisualStyleBackColor = true;
            this.chkError.CheckedChanged += new System.EventHandler(this.chkError_CheckedChanged);
            // 
            // pVariable
            // 
            this.pVariable.Controls.Add(this.txtDecimalPoints);
            this.pVariable.Controls.Add(this.label15);
            this.pVariable.Controls.Add(this.txtDeclaration);
            this.pVariable.Controls.Add(this.label14);
            this.pVariable.Controls.Add(this.txtReferenceName);
            this.pVariable.Controls.Add(this.label13);
            this.pVariable.Controls.Add(this.chkEvents);
            this.pVariable.Controls.Add(this.txtIndex);
            this.pVariable.Controls.Add(this.label11);
            this.pVariable.Controls.Add(this.txtName);
            this.pVariable.Controls.Add(this.label10);
            this.pVariable.Controls.Add(this.txtInstance);
            this.pVariable.Controls.Add(this.label9);
            this.pVariable.Controls.Add(this.txtRemark);
            this.pVariable.Controls.Add(this.label8);
            this.pVariable.Controls.Add(this.chkRemote);
            this.pVariable.Controls.Add(this.chkGlobal);
            this.pVariable.Controls.Add(this.chkNotConnected);
            this.pVariable.Controls.Add(this.chkPrivate);
            this.pVariable.Controls.Add(this.chkIOVar);
            this.pVariable.Controls.Add(this.chkConfValue);
            this.pVariable.Controls.Add(this.chkConstant);
            this.pVariable.Controls.Add(this.chkParameter);
            this.pVariable.Controls.Add(this.chkRetentive);
            this.pVariable.Controls.Add(this.chkLocal);
            this.pVariable.Controls.Add(this.chkTrending);
            this.pVariable.Controls.Add(this.txtVariableValue);
            this.pVariable.Controls.Add(this.label7);
            this.pVariable.Controls.Add(this.txtVariableType);
            this.pVariable.Controls.Add(this.label6);
            this.pVariable.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pVariable.Location = new System.Drawing.Point(0, 0);
            this.pVariable.Name = "pVariable";
            this.pVariable.Size = new System.Drawing.Size(584, 411);
            this.pVariable.TabIndex = 8;
            // 
            // chkEvents
            // 
            this.chkEvents.AutoSize = true;
            this.chkEvents.Location = new System.Drawing.Point(6, 6);
            this.chkEvents.Name = "chkEvents";
            this.chkEvents.Size = new System.Drawing.Size(116, 17);
            this.chkEvents.TabIndex = 23;
            this.chkEvents.Text = "Check for changes";
            this.chkEvents.UseVisualStyleBackColor = true;
            this.chkEvents.CheckedChanged += new System.EventHandler(this.chkEvents_CheckedChanged);
            // 
            // txtIndex
            // 
            this.txtIndex.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtIndex.Location = new System.Drawing.Point(100, 90);
            this.txtIndex.Name = "txtIndex";
            this.txtIndex.ReadOnly = true;
            this.txtIndex.Size = new System.Drawing.Size(481, 20);
            this.txtIndex.TabIndex = 22;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(3, 93);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(36, 13);
            this.label11.TabIndex = 21;
            this.label11.Text = "Index:";
            // 
            // txtName
            // 
            this.txtName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtName.Location = new System.Drawing.Point(100, 64);
            this.txtName.Name = "txtName";
            this.txtName.ReadOnly = true;
            this.txtName.Size = new System.Drawing.Size(481, 20);
            this.txtName.TabIndex = 20;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(3, 67);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(38, 13);
            this.label10.TabIndex = 19;
            this.label10.Text = "Name:";
            // 
            // txtInstance
            // 
            this.txtInstance.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtInstance.Location = new System.Drawing.Point(100, 38);
            this.txtInstance.Name = "txtInstance";
            this.txtInstance.ReadOnly = true;
            this.txtInstance.Size = new System.Drawing.Size(481, 20);
            this.txtInstance.TabIndex = 18;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(3, 41);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(51, 13);
            this.label9.TabIndex = 17;
            this.label9.Text = "Instance:";
            // 
            // txtRemark
            // 
            this.txtRemark.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtRemark.Location = new System.Drawing.Point(100, 142);
            this.txtRemark.Name = "txtRemark";
            this.txtRemark.ReadOnly = true;
            this.txtRemark.Size = new System.Drawing.Size(481, 20);
            this.txtRemark.TabIndex = 16;
            this.txtRemark.TextChanged += new System.EventHandler(this.txtRemark_TextChanged);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(3, 145);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(47, 13);
            this.label8.TabIndex = 15;
            this.label8.Text = "Remark:";
            // 
            // chkRemote
            // 
            this.chkRemote.AutoSize = true;
            this.chkRemote.Enabled = false;
            this.chkRemote.Location = new System.Drawing.Point(369, 368);
            this.chkRemote.Name = "chkRemote";
            this.chkRemote.Size = new System.Drawing.Size(63, 17);
            this.chkRemote.TabIndex = 14;
            this.chkRemote.Text = "Remote";
            this.chkRemote.UseVisualStyleBackColor = true;
            // 
            // chkGlobal
            // 
            this.chkGlobal.AutoSize = true;
            this.chkGlobal.Enabled = false;
            this.chkGlobal.Location = new System.Drawing.Point(307, 368);
            this.chkGlobal.Name = "chkGlobal";
            this.chkGlobal.Size = new System.Drawing.Size(56, 17);
            this.chkGlobal.TabIndex = 13;
            this.chkGlobal.Text = "Global";
            this.chkGlobal.UseVisualStyleBackColor = true;
            // 
            // chkNotConnected
            // 
            this.chkNotConnected.AutoSize = true;
            this.chkNotConnected.Enabled = false;
            this.chkNotConnected.Location = new System.Drawing.Point(307, 391);
            this.chkNotConnected.Name = "chkNotConnected";
            this.chkNotConnected.Size = new System.Drawing.Size(41, 17);
            this.chkNotConnected.TabIndex = 12;
            this.chkNotConnected.Text = "NC";
            this.chkNotConnected.UseVisualStyleBackColor = true;
            // 
            // chkPrivate
            // 
            this.chkPrivate.AutoSize = true;
            this.chkPrivate.Enabled = false;
            this.chkPrivate.Location = new System.Drawing.Point(245, 368);
            this.chkPrivate.Name = "chkPrivate";
            this.chkPrivate.Size = new System.Drawing.Size(59, 17);
            this.chkPrivate.TabIndex = 11;
            this.chkPrivate.Text = "Private";
            this.chkPrivate.UseVisualStyleBackColor = true;
            // 
            // chkIOVar
            // 
            this.chkIOVar.AutoSize = true;
            this.chkIOVar.Enabled = false;
            this.chkIOVar.Location = new System.Drawing.Point(245, 391);
            this.chkIOVar.Name = "chkIOVar";
            this.chkIOVar.Size = new System.Drawing.Size(56, 17);
            this.chkIOVar.TabIndex = 10;
            this.chkIOVar.Text = "IO Var";
            this.chkIOVar.UseVisualStyleBackColor = true;
            // 
            // chkConfValue
            // 
            this.chkConfValue.AutoSize = true;
            this.chkConfValue.Enabled = false;
            this.chkConfValue.Location = new System.Drawing.Point(158, 391);
            this.chkConfValue.Name = "chkConfValue";
            this.chkConfValue.Size = new System.Drawing.Size(81, 17);
            this.chkConfValue.TabIndex = 9;
            this.chkConfValue.Text = "Conf. Value";
            this.chkConfValue.UseVisualStyleBackColor = true;
            // 
            // chkConstant
            // 
            this.chkConstant.AutoSize = true;
            this.chkConstant.Enabled = false;
            this.chkConstant.Location = new System.Drawing.Point(158, 368);
            this.chkConstant.Name = "chkConstant";
            this.chkConstant.Size = new System.Drawing.Size(68, 17);
            this.chkConstant.TabIndex = 8;
            this.chkConstant.Text = "Constant";
            this.chkConstant.UseVisualStyleBackColor = true;
            // 
            // chkParameter
            // 
            this.chkParameter.AutoSize = true;
            this.chkParameter.Enabled = false;
            this.chkParameter.Location = new System.Drawing.Point(80, 391);
            this.chkParameter.Name = "chkParameter";
            this.chkParameter.Size = new System.Drawing.Size(74, 17);
            this.chkParameter.TabIndex = 7;
            this.chkParameter.Text = "Parameter";
            this.chkParameter.UseVisualStyleBackColor = true;
            // 
            // chkRetentive
            // 
            this.chkRetentive.AutoSize = true;
            this.chkRetentive.Enabled = false;
            this.chkRetentive.Location = new System.Drawing.Point(80, 368);
            this.chkRetentive.Name = "chkRetentive";
            this.chkRetentive.Size = new System.Drawing.Size(72, 17);
            this.chkRetentive.TabIndex = 6;
            this.chkRetentive.Text = "Retentive";
            this.chkRetentive.UseVisualStyleBackColor = true;
            // 
            // chkLocal
            // 
            this.chkLocal.AutoSize = true;
            this.chkLocal.Enabled = false;
            this.chkLocal.Location = new System.Drawing.Point(6, 391);
            this.chkLocal.Name = "chkLocal";
            this.chkLocal.Size = new System.Drawing.Size(52, 17);
            this.chkLocal.TabIndex = 5;
            this.chkLocal.Text = "Local";
            this.chkLocal.UseVisualStyleBackColor = true;
            // 
            // chkTrending
            // 
            this.chkTrending.AutoSize = true;
            this.chkTrending.Enabled = false;
            this.chkTrending.Location = new System.Drawing.Point(6, 368);
            this.chkTrending.Name = "chkTrending";
            this.chkTrending.Size = new System.Drawing.Size(68, 17);
            this.chkTrending.TabIndex = 4;
            this.chkTrending.Text = "Trending";
            this.chkTrending.UseVisualStyleBackColor = true;
            // 
            // txtVariableValue
            // 
            this.txtVariableValue.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtVariableValue.Location = new System.Drawing.Point(100, 246);
            this.txtVariableValue.Name = "txtVariableValue";
            this.txtVariableValue.Size = new System.Drawing.Size(481, 20);
            this.txtVariableValue.TabIndex = 3;
            this.txtVariableValue.TextChanged += new System.EventHandler(this.txtVariableValue_TextChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(3, 249);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(37, 13);
            this.label7.TabIndex = 2;
            this.label7.Text = "Value:";
            // 
            // txtVariableType
            // 
            this.txtVariableType.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtVariableType.Location = new System.Drawing.Point(100, 116);
            this.txtVariableType.Name = "txtVariableType";
            this.txtVariableType.ReadOnly = true;
            this.txtVariableType.Size = new System.Drawing.Size(481, 20);
            this.txtVariableType.TabIndex = 1;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(3, 119);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(34, 13);
            this.label6.TabIndex = 0;
            this.label6.Text = "Type:";
            // 
            // txtStatusVariableName
            // 
            this.txtStatusVariableName.Location = new System.Drawing.Point(405, 6);
            this.txtStatusVariableName.Name = "txtStatusVariableName";
            this.txtStatusVariableName.Size = new System.Drawing.Size(118, 20);
            this.txtStatusVariableName.TabIndex = 7;
            this.txtStatusVariableName.Text = "Status";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(290, 9);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(112, 13);
            this.label4.TabIndex = 8;
            this.label4.Text = "Status Variable Name:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(529, 9);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(108, 13);
            this.label5.TabIndex = 9;
            this.label5.Text = "Alarm Variable Name:";
            // 
            // txtAlarmVariableName
            // 
            this.txtAlarmVariableName.Location = new System.Drawing.Point(640, 6);
            this.txtAlarmVariableName.Name = "txtAlarmVariableName";
            this.txtAlarmVariableName.Size = new System.Drawing.Size(118, 20);
            this.txtAlarmVariableName.TabIndex = 10;
            this.txtAlarmVariableName.Text = "err";
            // 
            // txtReferenceName
            // 
            this.txtReferenceName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtReferenceName.Location = new System.Drawing.Point(100, 168);
            this.txtReferenceName.Name = "txtReferenceName";
            this.txtReferenceName.ReadOnly = true;
            this.txtReferenceName.Size = new System.Drawing.Size(481, 20);
            this.txtReferenceName.TabIndex = 25;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(3, 171);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(91, 13);
            this.label13.TabIndex = 24;
            this.label13.Text = "Reference Name:";
            // 
            // txtDeclaration
            // 
            this.txtDeclaration.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtDeclaration.Location = new System.Drawing.Point(100, 194);
            this.txtDeclaration.Name = "txtDeclaration";
            this.txtDeclaration.ReadOnly = true;
            this.txtDeclaration.Size = new System.Drawing.Size(481, 20);
            this.txtDeclaration.TabIndex = 27;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(3, 197);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(64, 13);
            this.label14.TabIndex = 26;
            this.label14.Text = "Declaration:";
            // 
            // txtDecimalPoints
            // 
            this.txtDecimalPoints.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtDecimalPoints.Location = new System.Drawing.Point(100, 220);
            this.txtDecimalPoints.Name = "txtDecimalPoints";
            this.txtDecimalPoints.ReadOnly = true;
            this.txtDecimalPoints.Size = new System.Drawing.Size(481, 20);
            this.txtDecimalPoints.TabIndex = 29;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(3, 223);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(80, 13);
            this.label15.TabIndex = 28;
            this.label15.Text = "Decimal Points:";
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(859, 580);
            this.Controls.Add(this.txtAlarmVariableName);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.txtStatusVariableName);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.bnSetClassName);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txtClassName);
            this.Name = "frmMain";
            this.Text = "aXLibraryTest";
            this.Load += new System.EventHandler(this.frmMain_Load);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.Panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer1)).EndInit();
            this.splitContainer1.ResumeLayout(false);
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.splitContainer2)).EndInit();
            this.splitContainer2.ResumeLayout(false);
            this.pInstance.ResumeLayout(false);
            this.pInstance.PerformLayout();
            this.pVariable.ResumeLayout(false);
            this.pVariable.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txtLog;
        private System.Windows.Forms.TextBox txtClassName;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button bnSetClassName;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.SplitContainer splitContainer2;
        private System.Windows.Forms.TreeView tvInstances;
        private System.Windows.Forms.Panel pInstance;
        private System.Windows.Forms.TextBox txtInstanceRemark;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtError;
        private System.Windows.Forms.TextBox txtStatus;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.CheckBox chkError;
        private System.Windows.Forms.TextBox txtStatusVariableName;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txtAlarmVariableName;
        private System.Windows.Forms.Panel pVariable;
        private System.Windows.Forms.TextBox txtVariableType;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox txtVariableValue;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.CheckBox chkTrending;
        private System.Windows.Forms.CheckBox chkPrivate;
        private System.Windows.Forms.CheckBox chkIOVar;
        private System.Windows.Forms.CheckBox chkConfValue;
        private System.Windows.Forms.CheckBox chkConstant;
        private System.Windows.Forms.CheckBox chkParameter;
        private System.Windows.Forms.CheckBox chkRetentive;
        private System.Windows.Forms.CheckBox chkLocal;
        private System.Windows.Forms.CheckBox chkNotConnected;
        private System.Windows.Forms.CheckBox chkGlobal;
        private System.Windows.Forms.CheckBox chkRemote;
        private System.Windows.Forms.TextBox txtRemark;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox txtIndex;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox txtName;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox txtInstance;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.CheckBox chkEvents;
        private System.Windows.Forms.TextBox txtInstanceName;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox txtDeclaration;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.TextBox txtReferenceName;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.TextBox txtDecimalPoints;
        private System.Windows.Forms.Label label15;
    }
}

