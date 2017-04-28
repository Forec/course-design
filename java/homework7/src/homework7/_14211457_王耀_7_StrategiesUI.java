package homework7;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JLabel;

import java.awt.Font;

import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JButton;
import javax.swing.JTable;
import javax.swing.ListSelectionModel;
import javax.swing.SwingConstants;
import javax.swing.table.DefaultTableCellRenderer;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Toolkit;

public class _14211457_王耀_7_StrategiesUI extends JFrame {

	private static final long serialVersionUID = 1L;
	private JPanel contentPane;
	private JTable table;
	private _14211457_王耀_7_mainUI parent;
	private _14211457_王耀_7_Observer observer;
	
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
	
	private void SuccessDia(String succmsg){
		JOptionPane.showMessageDialog(
				null, 
				succmsg, 
				"删除成功", 
				JOptionPane.PLAIN_MESSAGE); 
	}
	
	class StrategyUIObserver implements _14211457_王耀_7_Observer{
		public void update(){
			_14211457_王耀_7_NoEditTableModel model = (_14211457_王耀_7_NoEditTableModel) table.getModel();
		    if (model.getRowCount() > 0) {
		        for (int i = model.getRowCount() - 1; i > -1; i--) {
		            model.removeRow(i);
		        }
		    }
		    String type = "无折扣";
		    for (_14211457_王耀_7_IPricingStrategy ip: _14211457_王耀_7_StrategyManager.getInstance().getStrategies()){
		    	if (ip.getStrategyNumber() == 0){
		    		continue;
		    	}
		    	if (ip instanceof _14211457_王耀_7_CompositeStrategy){
		    		type = "组合策略";
		    	} else {
		    		if (ip instanceof _14211457_王耀_7_FlatRateStrategy)
		    			type = "绝对值优惠";
		    		if (ip instanceof _14211457_王耀_7_PercentageStrategy)
		    			type = "百分比优惠";
		    	}
				model.addRow(new Object[]{
						ip.getStrategyNumber() + "", 
						ip.getStrategyName(), 
						ip.getStrategyValues(),
						type,
						_14211457_王耀_7_BookSpecification.getTypeName(ip.getBookType())});
			}
		}
	}
		
	
	public _14211457_王耀_7_StrategiesUI(_14211457_王耀_7_mainUI parentUI) {
		setIconImage(Toolkit.getDefaultToolkit().getImage(_14211457_王耀_7_StrategiesUI.class.getResource("/com/sun/javafx/scene/web/skin/IncreaseIndent_16x16_JFX.png")));
		setTitle("策略管理");
		parent = parentUI;
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				_14211457_王耀_7_StrategyManager.getInstance().removeObserver(observer);
				parent.getFrame().setEnabled(true);
			}
		});
		observer = new StrategyUIObserver();
		_14211457_王耀_7_StrategyManager.getInstance().registerObserver(observer);
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setBounds(100, 100, 570, 323);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JLabel label = new JLabel("策略管理");
		label.setFont(new Font("微软雅黑", Font.BOLD, 26));
		label.setBounds(223, 24, 129, 28);
		contentPane.add(label);
		
		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setBounds(10, 62, 533, 167);
		contentPane.add(scrollPane);
		
		table = new JTable();
		table.setFont(new Font("微软雅黑", Font.PLAIN, 13));
		table.setModel(new _14211457_王耀_7_NoEditTableModel(
			new Object[][] {
			},
			new String[] {
				"\u7B56\u7565\u7F16\u53F7", "\u7B56\u7565\u540D\u79F0", "\u7B56\u7565\u503C", "\u7B56\u7565\u7C7B\u578B", "\u9002\u7528\u4E66\u7C4D\u7C7B\u578B"
			}
		));
		table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		DefaultTableCellRenderer tcr = new DefaultTableCellRenderer();
		tcr.setHorizontalAlignment(SwingConstants.CENTER);
		table.setDefaultRenderer(Object.class, tcr);
		table.getTableHeader().setReorderingAllowed(false);
		table.getTableHeader().setResizingAllowed(false);
	    table.getColumnModel().getColumn(0).setPreferredWidth(10);
	    table.getColumnModel().getColumn(1).setPreferredWidth(80);
	    table.getColumnModel().getColumn(2).setPreferredWidth(40);
	    table.getColumnModel().getColumn(3).setPreferredWidth(80);
		scrollPane.setViewportView(table);
		
		JButton button = new JButton("新建策略");
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				changeToNewStrategy(null);
			}
		});
		button.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		button.setBounds(62, 239, 94, 34);
		contentPane.add(button);
		
		JButton button_1 = new JButton("返回主界面");
		button_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				close();
			}
		});
		button_1.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		button_1.setBounds(433, 239, 110, 34);
		contentPane.add(button_1);
		
		JButton button_2 = new JButton("删除选中策略");
		button_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				int selectedRow = table.getSelectedRow();
				if (selectedRow < 0){
					ErrorDia("您尚未选中任何策略！");
					return;
				}
				_14211457_王耀_7_NoEditTableModel model = (_14211457_王耀_7_NoEditTableModel) table.getModel();
				String strategyLineNumberText = (String) model.getValueAt(selectedRow, 0);
				int strategyLineNumber = -1;
				try{
					strategyLineNumber = Integer.parseInt(strategyLineNumberText);
				} catch (Exception e1){
					ErrorDia("您选中的策略格式不合法");
				}
				if (strategyLineNumber == 0){
					ErrorDia("默认的无折扣策略无法被删除！");
					return;
				}
				if (strategyLineNumber != -1 && 
						_14211457_王耀_7_Controller.getInstance().RemoveStrategy(strategyLineNumber) != null){
						SuccessDia("您选中的策略已经成功删除！");
						_14211457_王耀_7_Controller.getInstance().updateSale();
						_14211457_王耀_7_Controller.getInstance().updateStrategy();
				} else {
					ErrorDia("删除失败，您未选中任何策略或选中策略异常。");
				}
			}
		});
		button_2.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		button_2.setBounds(305, 239, 118, 34);
		contentPane.add(button_2);
		
		JButton button_3 = new JButton("编辑选中策略");
		button_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				int selectedRow = table.getSelectedRow();
				if (selectedRow < 0){
					ErrorDia("您尚未选中任何策略！");
					return;
				}
				
				_14211457_王耀_7_NoEditTableModel model = (_14211457_王耀_7_NoEditTableModel) table.getModel();
				Object strategyNumberText = model.getValueAt(selectedRow, 0);
				int strategyNumber = 0;
				try{
					strategyNumber = Integer.parseInt((String)strategyNumberText);
				} catch(Exception e1){
					ErrorDia("您选中的策略有误！");
					return;
				}
				changeToNewStrategy(_14211457_王耀_7_Controller.getInstance().getStrategy(strategyNumber));
			}
		});
		button_3.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		button_3.setBounds(166, 239, 129, 34);
		contentPane.add(button_3);
		_14211457_王耀_7_Controller.getInstance().updateStrategy();
	}
	
	private void changeToNewStrategy(_14211457_王耀_7_IPricingStrategy strategy){
		_14211457_王耀_7_AddStrategyUI addStrategyUI = new _14211457_王耀_7_AddStrategyUI(this);
		if (strategy != null){
			int type = -1;
			if (strategy instanceof _14211457_王耀_7_CompositeStrategy){
				type = 2;
			} else {
				if (strategy instanceof _14211457_王耀_7_FlatRateStrategy)
					type = 1;
				if (strategy instanceof _14211457_王耀_7_PercentageStrategy)
					type = 0;
			}
			if (type == -1){
				ErrorDia("默认的无折扣策略无法被编辑！");
				return;
			}
			addStrategyUI.setChange(strategy, type);
		}
		addStrategyUI.setVisible(true);
		addStrategyUI.setLocationRelativeTo(null);
		this.setEnabled(false);
	}
}
