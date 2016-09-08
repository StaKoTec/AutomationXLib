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
            this.txtInstanceRemark = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.pVariable = new System.Windows.Forms.Panel();
            this.txtDecimalPoints = new System.Windows.Forms.TextBox();
            this.label15 = new System.Windows.Forms.Label();
            this.txtDeclaration = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.txtReferenceName = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
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
            this.label17 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.txtCycleTime = new System.Windows.Forms.TextBox();
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
            this.txtLog.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.txtLog.Multiline = true;
            this.txtLog.Name = "txtLog";
            this.txtLog.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txtLog.Size = new System.Drawing.Size(1252, 187);
            this.txtLog.TabIndex = 2;
            // 
            // txtClassName
            // 
            this.txtClassName.Location = new System.Drawing.Point(118, 9);
            this.txtClassName.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.txtClassName.Name = "txtClassName";
            this.txtClassName.Size = new System.Drawing.Size(306, 26);
            this.txtClassName.TabIndex = 3;
            this.txtClassName.Text = "HomeGear";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(14, 14);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(98, 20);
            this.label1.TabIndex = 4;
            this.label1.Text = "Class Name:";
            // 
            // bnSetClassName
            // 
            this.bnSetClassName.Location = new System.Drawing.Point(638, 7);
            this.bnSetClassName.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.bnSetClassName.Name = "bnSetClassName";
            this.bnSetClassName.Size = new System.Drawing.Size(72, 31);
            this.bnSetClassName.TabIndex = 5;
            this.bnSetClassName.Text = "Set";
            this.bnSetClassName.UseVisualStyleBackColor = true;
            this.bnSetClassName.Click += new System.EventHandler(this.bnSetClassName_Click);
            // 
            // splitContainer1
            // 
            this.splitContainer1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.splitContainer1.Location = new System.Drawing.Point(18, 49);
            this.splitContainer1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
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
            this.splitContainer1.Size = new System.Drawing.Size(1252, 825);
            this.splitContainer1.SplitterDistance = 632;
            this.splitContainer1.SplitterWidth = 6;
            this.splitContainer1.TabIndex = 6;
            // 
            // splitContainer2
            // 
            this.splitContainer2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer2.Location = new System.Drawing.Point(0, 0);
            this.splitContainer2.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.splitContainer2.Name = "splitContainer2";
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.Controls.Add(this.tvInstances);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.pInstance);
            this.splitContainer2.Panel2.Controls.Add(this.pVariable);
            this.splitContainer2.Size = new System.Drawing.Size(1252, 632);
            this.splitContainer2.SplitterDistance = 370;
            this.splitContainer2.SplitterWidth = 6;
            this.splitContainer2.TabIndex = 0;
            // 
            // tvInstances
            // 
            this.tvInstances.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tvInstances.Location = new System.Drawing.Point(0, 0);
            this.tvInstances.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.tvInstances.Name = "tvInstances";
            this.tvInstances.Size = new System.Drawing.Size(370, 632);
            this.tvInstances.TabIndex = 0;
            this.tvInstances.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.tvInstances_AfterSelect);
            // 
            // pInstance
            // 
            this.pInstance.Controls.Add(this.txtInstanceName);
            this.pInstance.Controls.Add(this.label12);
            this.pInstance.Controls.Add(this.txtInstanceRemark);
            this.pInstance.Controls.Add(this.label2);
            this.pInstance.Dock = System.Windows.Forms.DockStyle.Fill;
            this.pInstance.Location = new System.Drawing.Point(0, 0);
            this.pInstance.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.pInstance.Name = "pInstance";
            this.pInstance.Size = new System.Drawing.Size(876, 632);
            this.pInstance.TabIndex = 0;
            // 
            // txtInstanceName
            // 
            this.txtInstanceName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtInstanceName.Location = new System.Drawing.Point(84, 5);
            this.txtInstanceName.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.txtInstanceName.Name = "txtInstanceName";
            this.txtInstanceName.ReadOnly = true;
            this.txtInstanceName.Size = new System.Drawing.Size(786, 26);
            this.txtInstanceName.TabIndex = 8;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(4, 9);
            this.label12.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(55, 20);
            this.label12.TabIndex = 7;
            this.label12.Text = "Name:";
            // 
            // txtInstanceRemark
            // 
            this.txtInstanceRemark.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtInstanceRemark.Location = new System.Drawing.Point(84, 45);
            this.txtInstanceRemark.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.txtInstanceRemark.Name = "txtInstanceRemark";
            this.txtInstanceRemark.ReadOnly = true;
            this.txtInstanceRemark.Size = new System.Drawing.Size(786, 26);
            this.txtInstanceRemark.TabIndex = 1;
            this.txtInstanceRemark.TextChanged += new System.EventHandler(this.txtInstanceRemark_TextChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(4, 49);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(69, 20);
            this.label2.TabIndex = 0;
            this.label2.Text = "Remark:";
            // 
            // pVariable
            // 
            this.pVariable.Controls.Add(this.txtDecimalPoints);
            this.pVariable.Controls.Add(this.label15);
            this.pVariable.Controls.Add(this.txtDeclaration);
            this.pVariable.Controls.Add(this.label14);
            this.pVariable.Controls.Add(this.txtReferenceName);
            this.pVariable.Controls.Add(this.label13);
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
            this.pVariable.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.pVariable.Name = "pVariable";
            this.pVariable.Size = new System.Drawing.Size(876, 632);
            this.pVariable.TabIndex = 8;
            // 
            // txtDecimalPoints
            // 
            this.txtDecimalPoints.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtDecimalPoints.Location = new System.Drawing.Point(150, 285);
            this.txtDecimalPoints.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.txtDecimalPoints.Name = "txtDecimalPoints";
            this.txtDecimalPoints.ReadOnly = true;
            this.txtDecimalPoints.Size = new System.Drawing.Size(720, 26);
            this.txtDecimalPoints.TabIndex = 29;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(4, 289);
            this.label15.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(118, 20);
            this.label15.TabIndex = 28;
            this.label15.Text = "Decimal Points:";
            // 
            // txtDeclaration
            // 
            this.txtDeclaration.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtDeclaration.Location = new System.Drawing.Point(150, 245);
            this.txtDeclaration.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.txtDeclaration.Name = "txtDeclaration";
            this.txtDeclaration.ReadOnly = true;
            this.txtDeclaration.Size = new System.Drawing.Size(720, 26);
            this.txtDeclaration.TabIndex = 27;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(4, 249);
            this.label14.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(94, 20);
            this.label14.TabIndex = 26;
            this.label14.Text = "Declaration:";
            // 
            // txtReferenceName
            // 
            this.txtReferenceName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtReferenceName.Location = new System.Drawing.Point(150, 205);
            this.txtReferenceName.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.txtReferenceName.Name = "txtReferenceName";
            this.txtReferenceName.ReadOnly = true;
            this.txtReferenceName.Size = new System.Drawing.Size(720, 26);
            this.txtReferenceName.TabIndex = 25;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(4, 209);
            this.label13.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(134, 20);
            this.label13.TabIndex = 24;
            this.label13.Text = "Reference Name:";
            // 
            // txtIndex
            // 
            this.txtIndex.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtIndex.Location = new System.Drawing.Point(150, 85);
            this.txtIndex.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.txtIndex.Name = "txtIndex";
            this.txtIndex.ReadOnly = true;
            this.txtIndex.Size = new System.Drawing.Size(720, 26);
            this.txtIndex.TabIndex = 22;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(4, 89);
            this.label11.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(52, 20);
            this.label11.TabIndex = 21;
            this.label11.Text = "Index:";
            // 
            // txtName
            // 
            this.txtName.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtName.Location = new System.Drawing.Point(150, 45);
            this.txtName.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.txtName.Name = "txtName";
            this.txtName.ReadOnly = true;
            this.txtName.Size = new System.Drawing.Size(720, 26);
            this.txtName.TabIndex = 20;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(4, 49);
            this.label10.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(55, 20);
            this.label10.TabIndex = 19;
            this.label10.Text = "Name:";
            // 
            // txtInstance
            // 
            this.txtInstance.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtInstance.Location = new System.Drawing.Point(150, 5);
            this.txtInstance.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.txtInstance.Name = "txtInstance";
            this.txtInstance.ReadOnly = true;
            this.txtInstance.Size = new System.Drawing.Size(720, 26);
            this.txtInstance.TabIndex = 18;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(4, 9);
            this.label9.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(75, 20);
            this.label9.TabIndex = 17;
            this.label9.Text = "Instance:";
            // 
            // txtRemark
            // 
            this.txtRemark.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtRemark.Location = new System.Drawing.Point(150, 165);
            this.txtRemark.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.txtRemark.Name = "txtRemark";
            this.txtRemark.ReadOnly = true;
            this.txtRemark.Size = new System.Drawing.Size(720, 26);
            this.txtRemark.TabIndex = 16;
            this.txtRemark.TextChanged += new System.EventHandler(this.txtRemark_TextChanged);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(4, 169);
            this.label8.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(69, 20);
            this.label8.TabIndex = 15;
            this.label8.Text = "Remark:";
            // 
            // chkRemote
            // 
            this.chkRemote.AutoSize = true;
            this.chkRemote.Enabled = false;
            this.chkRemote.Location = new System.Drawing.Point(554, 566);
            this.chkRemote.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.chkRemote.Name = "chkRemote";
            this.chkRemote.Size = new System.Drawing.Size(92, 24);
            this.chkRemote.TabIndex = 14;
            this.chkRemote.Text = "Remote";
            this.chkRemote.UseVisualStyleBackColor = true;
            // 
            // chkGlobal
            // 
            this.chkGlobal.AutoSize = true;
            this.chkGlobal.Enabled = false;
            this.chkGlobal.Location = new System.Drawing.Point(460, 566);
            this.chkGlobal.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.chkGlobal.Name = "chkGlobal";
            this.chkGlobal.Size = new System.Drawing.Size(81, 24);
            this.chkGlobal.TabIndex = 13;
            this.chkGlobal.Text = "Global";
            this.chkGlobal.UseVisualStyleBackColor = true;
            // 
            // chkNotConnected
            // 
            this.chkNotConnected.AutoSize = true;
            this.chkNotConnected.Enabled = false;
            this.chkNotConnected.Location = new System.Drawing.Point(460, 602);
            this.chkNotConnected.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.chkNotConnected.Name = "chkNotConnected";
            this.chkNotConnected.Size = new System.Drawing.Size(57, 24);
            this.chkNotConnected.TabIndex = 12;
            this.chkNotConnected.Text = "NC";
            this.chkNotConnected.UseVisualStyleBackColor = true;
            // 
            // chkPrivate
            // 
            this.chkPrivate.AutoSize = true;
            this.chkPrivate.Enabled = false;
            this.chkPrivate.Location = new System.Drawing.Point(368, 566);
            this.chkPrivate.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.chkPrivate.Name = "chkPrivate";
            this.chkPrivate.Size = new System.Drawing.Size(83, 24);
            this.chkPrivate.TabIndex = 11;
            this.chkPrivate.Text = "Private";
            this.chkPrivate.UseVisualStyleBackColor = true;
            // 
            // chkIOVar
            // 
            this.chkIOVar.AutoSize = true;
            this.chkIOVar.Enabled = false;
            this.chkIOVar.Location = new System.Drawing.Point(368, 602);
            this.chkIOVar.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.chkIOVar.Name = "chkIOVar";
            this.chkIOVar.Size = new System.Drawing.Size(81, 24);
            this.chkIOVar.TabIndex = 10;
            this.chkIOVar.Text = "IO Var";
            this.chkIOVar.UseVisualStyleBackColor = true;
            // 
            // chkConfValue
            // 
            this.chkConfValue.AutoSize = true;
            this.chkConfValue.Enabled = false;
            this.chkConfValue.Location = new System.Drawing.Point(237, 602);
            this.chkConfValue.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.chkConfValue.Name = "chkConfValue";
            this.chkConfValue.Size = new System.Drawing.Size(118, 24);
            this.chkConfValue.TabIndex = 9;
            this.chkConfValue.Text = "Conf. Value";
            this.chkConfValue.UseVisualStyleBackColor = true;
            // 
            // chkConstant
            // 
            this.chkConstant.AutoSize = true;
            this.chkConstant.Enabled = false;
            this.chkConstant.Location = new System.Drawing.Point(237, 566);
            this.chkConstant.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.chkConstant.Name = "chkConstant";
            this.chkConstant.Size = new System.Drawing.Size(100, 24);
            this.chkConstant.TabIndex = 8;
            this.chkConstant.Text = "Constant";
            this.chkConstant.UseVisualStyleBackColor = true;
            // 
            // chkParameter
            // 
            this.chkParameter.AutoSize = true;
            this.chkParameter.Enabled = false;
            this.chkParameter.Location = new System.Drawing.Point(120, 602);
            this.chkParameter.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.chkParameter.Name = "chkParameter";
            this.chkParameter.Size = new System.Drawing.Size(109, 24);
            this.chkParameter.TabIndex = 7;
            this.chkParameter.Text = "Parameter";
            this.chkParameter.UseVisualStyleBackColor = true;
            // 
            // chkRetentive
            // 
            this.chkRetentive.AutoSize = true;
            this.chkRetentive.Enabled = false;
            this.chkRetentive.Location = new System.Drawing.Point(120, 566);
            this.chkRetentive.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.chkRetentive.Name = "chkRetentive";
            this.chkRetentive.Size = new System.Drawing.Size(103, 24);
            this.chkRetentive.TabIndex = 6;
            this.chkRetentive.Text = "Retentive";
            this.chkRetentive.UseVisualStyleBackColor = true;
            // 
            // chkLocal
            // 
            this.chkLocal.AutoSize = true;
            this.chkLocal.Enabled = false;
            this.chkLocal.Location = new System.Drawing.Point(9, 602);
            this.chkLocal.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.chkLocal.Name = "chkLocal";
            this.chkLocal.Size = new System.Drawing.Size(73, 24);
            this.chkLocal.TabIndex = 5;
            this.chkLocal.Text = "Local";
            this.chkLocal.UseVisualStyleBackColor = true;
            // 
            // chkTrending
            // 
            this.chkTrending.AutoSize = true;
            this.chkTrending.Enabled = false;
            this.chkTrending.Location = new System.Drawing.Point(9, 566);
            this.chkTrending.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.chkTrending.Name = "chkTrending";
            this.chkTrending.Size = new System.Drawing.Size(97, 24);
            this.chkTrending.TabIndex = 4;
            this.chkTrending.Text = "Trending";
            this.chkTrending.UseVisualStyleBackColor = true;
            // 
            // txtVariableValue
            // 
            this.txtVariableValue.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtVariableValue.Location = new System.Drawing.Point(150, 325);
            this.txtVariableValue.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.txtVariableValue.Name = "txtVariableValue";
            this.txtVariableValue.Size = new System.Drawing.Size(720, 26);
            this.txtVariableValue.TabIndex = 3;
            this.txtVariableValue.TextChanged += new System.EventHandler(this.txtVariableValue_TextChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(4, 329);
            this.label7.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(54, 20);
            this.label7.TabIndex = 2;
            this.label7.Text = "Value:";
            // 
            // txtVariableType
            // 
            this.txtVariableType.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtVariableType.Location = new System.Drawing.Point(150, 125);
            this.txtVariableType.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.txtVariableType.Name = "txtVariableType";
            this.txtVariableType.ReadOnly = true;
            this.txtVariableType.Size = new System.Drawing.Size(720, 26);
            this.txtVariableType.TabIndex = 1;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(4, 183);
            this.label6.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(47, 20);
            this.label6.TabIndex = 0;
            this.label6.Text = "Type:";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(600, 14);
            this.label17.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(30, 20);
            this.label17.TabIndex = 27;
            this.label17.Text = "ms";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(432, 12);
            this.label16.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(85, 20);
            this.label16.TabIndex = 26;
            this.label16.Text = "Cycle time:";
            // 
            // txtCycleTime
            // 
            this.txtCycleTime.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtCycleTime.Location = new System.Drawing.Point(525, 9);
            this.txtCycleTime.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.txtCycleTime.Name = "txtCycleTime";
            this.txtCycleTime.Size = new System.Drawing.Size(64, 26);
            this.txtCycleTime.TabIndex = 25;
            this.txtCycleTime.TextChanged += new System.EventHandler(this.txtCycleTime_TextChanged);
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(9F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1288, 892);
            this.Controls.Add(this.label17);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.label16);
            this.Controls.Add(this.bnSetClassName);
            this.Controls.Add(this.txtCycleTime);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txtClassName);
            this.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
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
        private System.Windows.Forms.TextBox txtInstanceName;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox txtDeclaration;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.TextBox txtReferenceName;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.TextBox txtDecimalPoints;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.TextBox txtCycleTime;
    }
}

