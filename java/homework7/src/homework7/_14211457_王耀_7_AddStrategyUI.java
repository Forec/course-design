package homework7;


import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JLabel;

import java.awt.Font;
import java.awt.event.WindowEvent;

import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.DefaultComboBoxModel;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.ItemListener;
import java.awt.event.ItemEvent;

public class _14211457_王耀_7_AddStrategyUI extends JFrame {

	private static final long serialVersionUID = 1L;
	private JPanel contentPane;
	private JTextField strategyNameField;
	private JTextField strategyValueField;
	private _14211457_王耀_7_StrategiesUI parent;
	private _14211457_王耀_7_IPricingStrategy tempStrategyInEditMode;
	private boolean editMode = false;
	private JLabel label;
	private JButton button;
	private JLabel label_4;
	private JComboBox<String> strategyTypeField;
	private JComboBox<String> bookTypeField;
	
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
	
	public void setChange(_14211457_王耀_7_IPricingStrategy strategy, int type){
		tempStrategyInEditMode = strategy;
		editMode = true;
		label.setText("修改策略");
		button.setText("确认修改");
		strategyNameField.setText(strategy.getStrategyName());
		strategyValueField.setText(strategy.getStrategyValues());
		strategyTypeField.setSelectedIndex(type);
		bookTypeField.setSelectedIndex(strategy.getBookType());
		strategyTypeField.setEnabled(false);
		changeType();
	}
	
	private void changeType(){
		int type = strategyTypeField.getSelectedIndex();
		if (type == 2){	// 组合模式
			label_4.setVisible(false);
		} else {
			label_4.setVisible(true);
			if (type == 1){	// 绝对值
				label_4.setText("元/本");
			} else{
				label_4.setText("%/本");
			}
		}
	}

	public _14211457_王耀_7_AddStrategyUI(_14211457_王耀_7_StrategiesUI parentUI) {
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				parent.setEnabled(true);
			}
		});
		parent = parentUI;
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setBounds(100, 100, 450, 319);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		label = new JLabel("添加策略");
		label.setFont(new Font("微软雅黑", Font.BOLD, 22));
		label.setBounds(166, 34, 119, 26);
		contentPane.add(label);
		
		strategyNameField = new JTextField();
		strategyNameField.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		strategyNameField.setColumns(10);
		strategyNameField.setBounds(148, 70, 217, 26);
		contentPane.add(strategyNameField);
		
		JLabel label_1 = new JLabel("策略名称");
		label_1.setFont(new Font("微软雅黑", Font.PLAIN, 15));
		label_1.setBounds(77, 70, 61, 26);
		contentPane.add(label_1);
		
		button = new JButton("确认添加");
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String name = strategyNameField.getText();
				int type = strategyTypeField.getSelectedIndex();
				int booktype = bookTypeField.getSelectedIndex();
				String value = strategyValueField.getText();
				double discount = 0;
				int percentageValue = 0;
				if (type < 0 || type > 2){
					ErrorDia("您尚未为新策略选择一种合法的类型");
					return;
				}
				if (booktype < 0 || booktype > 5){
					ErrorDia("您尚未为新策略选择一种合法的应用方式");
					return;
				}
				_14211457_王耀_7_IPricingStrategy _tempStrategy = _14211457_王耀_7_StrategyManager.getInstance().HasBookTypeOccupied(booktype);
				if (null != _tempStrategy && _tempStrategy != tempStrategyInEditMode){
					ErrorDia("您所选择的“" + _14211457_王耀_7_BookSpecification.getTypeName(booktype) +
							"” 已经被策略 “" + _tempStrategy.getStrategyName() + "” 应用！您需要先将" +
							"已应用到该类图书的其他策略移除才可为该类图书添加新策略！");
					return;
				}
				if (type == 2){	// 组合策略
			    	if (!_14211457_王耀_7_StrategyManager.tryStrategyValues(value)){
			    		ErrorDia("您输入的组合策略值不合法，请使用字符 '|' 分隔策略编号！");
						return;
			    	}
				} else {		// 简单策略
					if (type == 1){	// 绝对值，double
						try{
							discount = Float.parseFloat(value);
							if (discount <= 0){
				    			ErrorDia("您输入的优惠绝对值不合法，必须为大于 0 的实数！");
								return;
							}
						} catch (Exception e1){
			    			ErrorDia("您输入的优惠绝对值不合法，必须为大于 0 的实数！");
							return;
						}
					} else{		// 百分比策略
						try{
							percentageValue = Integer.parseInt(value);
							if (percentageValue <= 0 || percentageValue > 100){
				    			ErrorDia("您输入的优惠百分比不合法，必须为 0 ~ 100 之间的整数！");
								return;
							}
						} catch (Exception e1){
			    			ErrorDia("您输入的优惠百分比不合法，必须为 0 ~ 100 之间的整数！");
							return;
						}
					}
				}
				if (!editMode){
					_14211457_王耀_7_IPricingStrategy newStrategy = null;
					if (type == 2){
						newStrategy = new _14211457_王耀_7_CustomerBestStrategy(name);
						newStrategy.setStrategyValue(value);
					} else if (type == 1){
						newStrategy = new _14211457_王耀_7_FlatRateStrategy(name, discount);
					} else {
						newStrategy = new _14211457_王耀_7_PercentageStrategy(name, percentageValue);
					}
					if (!newStrategy.setBookType(booktype)){
						ErrorDia("您为策略选择的应用图书类型已被其他策略占用！");
						return;
					}
					_14211457_王耀_7_Controller.getInstance().AddStrategy(newStrategy);
				} else if (tempStrategyInEditMode != null){
					tempStrategyInEditMode.setStrategyName(name);
					tempStrategyInEditMode.setStrategyValue(value);
					if (!tempStrategyInEditMode.setBookType(booktype))
						ErrorDia("您为策略选择的应用图书类型已被其他策略占用！");
				}
				_14211457_王耀_7_Controller.getInstance().updateStrategy();
				_14211457_王耀_7_Controller.getInstance().getShoppingCart().updateStrategy();
				_14211457_王耀_7_Controller.getInstance().updateSale();
				close();
			}
		});
		button.setFont(new Font("微软雅黑", Font.PLAIN, 15));
		button.setBounds(110, 217, 105, 31);
		contentPane.add(button);
		
		JButton button_1 = new JButton("返回主界面");
		button_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				close();
			}
		});
		button_1.setFont(new Font("微软雅黑", Font.PLAIN, 15));
		button_1.setBounds(225, 217, 119, 31);
		contentPane.add(button_1);
		
		JLabel label_2 = new JLabel("策略类型");
		label_2.setFont(new Font("微软雅黑", Font.PLAIN, 15));
		label_2.setBounds(77, 106, 61, 26);
		contentPane.add(label_2);
		
		strategyTypeField = new JComboBox<String>();
		strategyTypeField.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		strategyTypeField.addItemListener(new ItemListener() {
			public void itemStateChanged(ItemEvent e) {
				if (e.getStateChange() == ItemEvent.SELECTED){ 
					changeType();
				}
			}
		});
		strategyTypeField.setModel(new DefaultComboBoxModel<String>(new String[] {"百分比折扣策略", "绝对值优惠策略", "组合策略"}));
		strategyTypeField.setBounds(148, 106, 217, 26);
		contentPane.add(strategyTypeField);
		
		JLabel label_3 = new JLabel("策略值");
		label_3.setFont(new Font("微软雅黑", Font.PLAIN, 15));
		label_3.setBounds(77, 181, 61, 26);
		contentPane.add(label_3);
		
		strategyValueField = new JTextField();
		strategyValueField.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		strategyValueField.setColumns(10);
		strategyValueField.setBounds(148, 181, 176, 26);
		contentPane.add(strategyValueField);
		
		label_4 = new JLabel("元/本");
		label_4.setFont(new Font("微软雅黑", Font.PLAIN, 15));
		label_4.setBounds(334, 179, 41, 26);
		contentPane.add(label_4);
		
		bookTypeField = new JComboBox<String>();
		bookTypeField.setModel(new DefaultComboBoxModel<String>(new String[] {"暂不应用此策略", "非教材类计算机图书", "教材类图书", "连环画类图书", "养生类图书", "其他"}));
		bookTypeField.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		bookTypeField.setBounds(148, 145, 217, 26);
		contentPane.add(bookTypeField);
		
		JLabel label_5 = new JLabel("适用图书");
		label_5.setFont(new Font("微软雅黑", Font.PLAIN, 15));
		label_5.setBounds(77, 145, 61, 26);
		contentPane.add(label_5);
		changeType();
	}
}
