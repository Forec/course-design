package homework4;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.JButton;

import java.awt.Color;

import javax.swing.JComboBox;
import javax.swing.DefaultComboBoxModel;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.ItemListener;
import java.awt.event.ItemEvent;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.Font;
import java.awt.Toolkit;

@SuppressWarnings("serial")
public class _14211457_王耀_4_InputEmployee extends JFrame {
	private JTextField socialSecureNumber;
	private JTextField comission;
	private JTextField lastName;
	private JTextField firstName;
	private JTextField gross;
	private JTextField basis;
	private JLabel typeLabel;
	private JLabel socialSecureLabel;
	private JLabel comissionLabel;
	private JLabel lastNameLabel;
	private JLabel firstNameLabel;
	private JLabel basisLabel;
	private JLabel grossLabel;
	private JButton button;
	private JButton button_1;
	private JComboBox<String> typeSelect;
	private _14211457_王耀_4_EmployeeManager parent;
	private _14211457_王耀_4_EmployeeFactory employeeFactory;

	/**
	 * Launch the application.
	 */
	
	private void changeType(){
		int selectType = typeSelect.getSelectedIndex();
		switch (selectType) {
		case 0:
			comissionLabel.setText("工作小时数");
			comissionLabel.setVisible(true);
			comission.setVisible(true);
			grossLabel.setText("每小时工资");
			grossLabel.setVisible(true);
			gross.setVisible(true);
			basisLabel.setVisible(false);
			basis.setVisible(false);
			break;
		case 1:
			comissionLabel.setText("每周工资");
			comissionLabel.setVisible(true);
			comission.setVisible(true);
			grossLabel.setVisible(false);
			gross.setVisible(false);
			basisLabel.setVisible(false);
			basis.setVisible(false);
			break;
		case 2:
			comissionLabel.setText("提成率");
			comissionLabel.setVisible(true);
			comission.setVisible(true);
			grossLabel.setText("销售额");
			grossLabel.setVisible(true);
			gross.setVisible(true);
			basis.setVisible(false);
			basisLabel.setVisible(false);
			break;
		case 3:
			comissionLabel.setText("提成率");
			comissionLabel.setVisible(true);
			comission.setVisible(true);
			grossLabel.setText("销售额");
			grossLabel.setVisible(true);
			gross.setVisible(true);
			basisLabel.setText("基础工资");
			basisLabel.setVisible(true);
			basis.setVisible(true);
			break;
		default:
			break;
		}
	}
	
	private void close(){
		dispatchEvent(new WindowEvent(this, WindowEvent.WINDOW_CLOSING));
	}
	
	private void ErrorDia(String errormsg){
		JOptionPane.showMessageDialog(
				null, 
				errormsg, 
				"错误", 
				JOptionPane.ERROR_MESSAGE); 
	}

	public void SetTypeSelect(int type){
		typeSelect.setSelectedIndex(type);
		changeType();
	}
	/**
	 * Create the frame.
	 */
	public _14211457_王耀_4_InputEmployee(_14211457_王耀_4_EmployeeManager parentManager, _14211457_王耀_4_EmployeeFactory factory) {
		setIconImage(Toolkit.getDefaultToolkit().getImage(_14211457_王耀_4_InputEmployee.class.getResource("/javax/swing/plaf/metal/icons/ocean/menu.gif")));
		setTitle("添加新员工");
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosed(WindowEvent e) {
				parent.getFrame().setEnabled(true);
			}
			@Override
			public void windowClosing(WindowEvent e) {
				parent.getFrame().setEnabled(true);
			}
		});
		parent = parentManager;
		employeeFactory = factory;
		
		setBounds(100, 100, 402, 360);
		getContentPane().setLayout(null);
		
		typeLabel = new JLabel("员工类型");
		typeLabel.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		typeLabel.setBounds(50, 48, 73, 15);
		getContentPane().add(typeLabel);
		
		socialSecureLabel = new JLabel("社会保险号");
		socialSecureLabel.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		socialSecureLabel.setBounds(50, 137, 73, 15);
		getContentPane().add(socialSecureLabel);
		
		socialSecureNumber = new JTextField();
		socialSecureNumber.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		socialSecureNumber.setBounds(124, 134, 205, 21);
		getContentPane().add(socialSecureNumber);
		socialSecureNumber.setColumns(10);
		
		comissionLabel = new JLabel("提成率");
		comissionLabel.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		comissionLabel.setBounds(50, 168, 73, 15);
		getContentPane().add(comissionLabel);
		
		comission = new JTextField();
		comission.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		comission.setColumns(10);
		comission.setBounds(124, 165, 205, 21);
		getContentPane().add(comission);
		
		lastNameLabel = new JLabel("姓");
		lastNameLabel.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		lastNameLabel.setBounds(50, 79, 73, 15);
		getContentPane().add(lastNameLabel);
		
		lastName = new JTextField();
		lastName.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		lastName.setColumns(10);
		lastName.setBounds(124, 76, 205, 21);
		getContentPane().add(lastName);
		
		firstName = new JTextField();
		firstName.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		firstName.setColumns(10);
		firstName.setBounds(124, 103, 205, 21);
		getContentPane().add(firstName);
		
		firstNameLabel = new JLabel("氏");
		firstNameLabel.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		firstNameLabel.setBounds(50, 104, 73, 15);
		getContentPane().add(firstNameLabel);
		
		basisLabel = new JLabel("基础工资");
		basisLabel.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		basisLabel.setBounds(50, 228, 73, 15);
		getContentPane().add(basisLabel);
		
		gross = new JTextField();
		gross.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		gross.setColumns(10);
		gross.setBounds(124, 192, 205, 21);
		getContentPane().add(gross);
		
		basis = new JTextField();
		basis.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		basis.setColumns(10);
		basis.setBounds(124, 225, 205, 21);
		getContentPane().add(basis);
		
		grossLabel = new JLabel("销售额");
		grossLabel.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		grossLabel.setBounds(50, 193, 73, 15);
		getContentPane().add(grossLabel);
		
		typeSelect = new JComboBox<String>();
		typeSelect.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		typeSelect.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent e) {
				if (e.getStateChange() == ItemEvent.SELECTED){ 
					changeType();
				}
			}
		});
		typeSelect.setModel(new DefaultComboBoxModel<String>(new String[] 
				{"小时工", "固定工资员工", "提成型员工", "工资+提成型员工"}
		));
		typeSelect.setBounds(124, 45, 205, 21);
		getContentPane().add(typeSelect);		
		
		button = new JButton("确认提交");
		button.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		button.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				int employeeIndex = typeSelect.getSelectedIndex();
				if (comission.isVisible() && comission.getText() == "" ||
                        gross.isVisible() && gross.getText() == "" ||
                        firstName.getText() == "" ||
                        lastName.getText() == "" ||
                        socialSecureNumber.getText() == "" ||
                        basis.isVisible() && basis.getText() == ""){
                    ErrorDia("请将信息填写完整");
                }
				_14211457_王耀_4_Employee employee;
				if (employeeIndex == 0){	// 小时工
					int hours, wage;
					try{
						hours = Integer.parseInt(comission.getText());
						wage = Integer.parseInt(gross.getText());
						employee = new _14211457_王耀_4_HourlyEmployee(
								firstName.getText(), 
								lastName.getText(), 
								socialSecureNumber.getText(),
								hours,
								wage
								);
					} catch (Exception error){
						ErrorDia("输入的数据格式不正确！");
						return;
					}
				} else if (employeeIndex  == 1){ 	// 固定工资员工
					int salary;
					try{
						salary = Integer.parseInt(comission.getText());
						employee = new _14211457_王耀_4_SalaridEmployee(
								firstName.getText(), 
								lastName.getText(), 
								socialSecureNumber.getText(),
								salary
								);
					} catch (Exception error){
						ErrorDia("输入的数据格式不正确！");
						return;
					}
				} else if (employeeIndex == 2){		// 提成员工
					float commison;
					int grossInt;
					try{
						commison = Float.parseFloat(comission.getText());
						grossInt = Integer.parseInt(gross.getText());
						if (commison > 1){
							ErrorDia("提成率不能大于 1 ！");
							return;
						}
						employee = new _14211457_王耀_4_CommissionEmployee(
								firstName.getText(), 
								lastName.getText(), 
								socialSecureNumber.getText(),
								grossInt,
								commison
								);
					} catch (Exception error){
						ErrorDia("输入的数据格式不正确！");
						return;
					}
				} else if (employeeIndex == 3){		// 工资+提成型员工
					float commison;
					int grossInt, basisSalary;
					try{
						commison = Float.parseFloat(comission.getText());
						if (commison > 1){
							ErrorDia("提成率不能大于 1 ！");
							return;
						}
						grossInt = Integer.parseInt(gross.getText());
						basisSalary = Integer.parseInt(basis.getText());
						employee = new _14211457_王耀_4_BasePlusCommissionEmployee(
								firstName.getText(), 
								lastName.getText(), 
								socialSecureNumber.getText(),
								grossInt,
								commison,
								basisSalary
								);
					} catch (Exception error){
						ErrorDia("输入的数据格式不正确！");
						return;
					}
				} else {
					ErrorDia("你没有选择任何一个合法的员工类型！");
					return;
				}
				employeeFactory.addEmployee(employee);
				parent.refresh();
				parent.getFrame().setEnabled(true);
				close();
				
			}
		});
		button.setForeground(Color.BLACK);
		button.setBackground(Color.GREEN);
		button.setBounds(154, 268, 93, 23);
		getContentPane().add(button);
		
		button_1 = new JButton("取消");
		button_1.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		button_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				close();
			}
		});
		button_1.setBounds(257, 268, 73, 23);
		getContentPane().add(button_1);
	}
}
