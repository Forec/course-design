package homework4;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.ListSelectionModel;
import javax.swing.SwingConstants;
import javax.swing.UIManager;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.BorderLayout;

import javax.swing.JScrollPane;

import java.util.List;

import javax.swing.JTable;
import javax.swing.plaf.FontUIResource;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.DefaultTableModel;

import java.awt.Font;

import javax.swing.ImageIcon;

import java.awt.Toolkit;

public class _14211457_王耀_4_EmployeeManager {

	private JFrame frame;
	private JMenu mnNewMenu;
	private JMenu mnNewMenu_1;
	private JMenuItem mntmNewMenuItem_2;
	private JMenuItem menuItem;
	private JMenuItem menuItem_1;
	private JMenuItem mntmNewMenuItem;
	private JMenuItem mntmNewMenuItem_1;
	private _14211457_王耀_4_EmployeeFactory factory;
	private JScrollPane scrollPane;
	private JTable table;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					UIManager.put("OptionPane.buttonFont", new FontUIResource(new Font("微软雅黑", Font.PLAIN, 14)));
					UIManager.put("OptionPane.messageFont", new FontUIResource(new Font("微软雅黑", Font.PLAIN, 14)));
					_14211457_王耀_4_EmployeeManager window = new _14211457_王耀_4_EmployeeManager();
					window.frame.setVisible(true);
					window.frame.setLocationRelativeTo(null); 
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
	
	class NoEditTableModel extends DefaultTableModel {  
		private static final long serialVersionUID = 1L;
		public NoEditTableModel(Object[][] data, Object[] columnNames) {  
	        super(data, columnNames);
	    }  
	    public boolean isCellEditable(int row, int column) {  
	        return false;
	    }  
	}  
	
	public JFrame getFrame(){
		return frame;
	}
	
	public void refresh(){
		NoEditTableModel model = (NoEditTableModel) table.getModel();
        if (model.getRowCount() > 0) {
            for (int i = model.getRowCount() - 1; i > -1; i--) {
                model.removeRow(i);
            }
        }
		List<_14211457_王耀_4_Employee> employeeList = factory.getEmployeeList();
		for (_14211457_王耀_4_Employee ep: employeeList){
			String etype;
			if (ep instanceof _14211457_王耀_4_HourlyEmployee){
				etype = "小时工";
			} else if (ep instanceof _14211457_王耀_4_SalaridEmployee){
				etype = "固定工资员工";
			} else if (ep instanceof _14211457_王耀_4_BasePlusCommissionEmployee){
				etype = "工资+提成型员工";
			} else if (ep instanceof _14211457_王耀_4_CommissionEmployee){
				etype = "提成型员工";						
			} else {
				continue;
			}
			model.addRow(new Object[]{
					etype, 
					ep.getSocialSecurityNumber(), 
					ep.getFirstName() + " " + ep.getLastName(),
					ep.earning()});
		}
	}

	/**
	 * Create the application.
	 */
	public _14211457_王耀_4_EmployeeManager() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		frame.setIconImage(Toolkit.getDefaultToolkit().getImage(_14211457_王耀_4_EmployeeManager.class.getResource("/javax/swing/plaf/metal/icons/ocean/computer.gif")));
		frame.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		frame.setTitle("员工管理系统");
		frame.setBounds(100, 100, 450, 300);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JMenuBar menuBar = new JMenuBar();
		frame.setJMenuBar(menuBar);
		
		mnNewMenu = new JMenu("录入新员工");
		mnNewMenu.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		menuBar.add(mnNewMenu);
		
		mntmNewMenuItem = new JMenuItem("提成型员工");
		mntmNewMenuItem.setIcon(new ImageIcon(_14211457_王耀_4_EmployeeManager.class.getResource("/javax/swing/plaf/metal/icons/sortUp.png")));
		mntmNewMenuItem.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		mntmNewMenuItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				CreateEmployee(2);
			}
		});
		
		menuItem = new JMenuItem("小时工");
		menuItem.setIcon(new ImageIcon(_14211457_王耀_4_EmployeeManager.class.getResource("/javax/swing/plaf/metal/icons/ocean/collapsed-rtl.gif")));
		menuItem.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		menuItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				CreateEmployee(0);
			}
		});
		mnNewMenu.add(menuItem);
		
		menuItem_1 = new JMenuItem("固定工资员工");
		menuItem_1.setIcon(new ImageIcon(_14211457_王耀_4_EmployeeManager.class.getResource("/javax/swing/plaf/metal/icons/ocean/expanded.gif")));
		menuItem_1.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		menuItem_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				CreateEmployee(1);
			}
		});
		mnNewMenu.add(menuItem_1);
		mnNewMenu.add(mntmNewMenuItem);
		
		mntmNewMenuItem_1 = new JMenuItem("工资+提成型员工");
		mntmNewMenuItem_1.setIcon(new ImageIcon(_14211457_王耀_4_EmployeeManager.class.getResource("/javax/swing/plaf/metal/icons/ocean/minimize.gif")));
		mntmNewMenuItem_1.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		mntmNewMenuItem_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				CreateEmployee(3);
			}
		});
		mnNewMenu.add(mntmNewMenuItem_1);
		
		mnNewMenu_1 = new JMenu("查询");
		mnNewMenu_1.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		menuBar.add(mnNewMenu_1);
		
		mntmNewMenuItem_2 = new JMenuItem("平均工资");
		mntmNewMenuItem_2.setIcon(new ImageIcon(_14211457_王耀_4_EmployeeManager.class.getResource("/com/sun/java/swing/plaf/windows/icons/DetailsView.gif")));
		mntmNewMenuItem_2.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		mntmNewMenuItem_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				JOptionPane.showMessageDialog(
						null, 
						"目前共有 " + factory.getEmployeesCount() +
						" 名员工，平均工资为 " + factory.getAverage() + "。", 
						"平均工资",
						JOptionPane.INFORMATION_MESSAGE); 
			}
		});
		mnNewMenu_1.add(mntmNewMenuItem_2);
		
		scrollPane = new JScrollPane();
		frame.getContentPane().add(scrollPane, BorderLayout.CENTER);
		
		table = new JTable();
		table.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		table.setModel(new NoEditTableModel(
			new Object[][] {
			},
			new String[] {
				"员工类型", "社会保险号", "姓名", "工资"
			}
		));
		table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		DefaultTableCellRenderer tcr = new DefaultTableCellRenderer();
		tcr.setHorizontalAlignment(SwingConstants.CENTER);
		table.setDefaultRenderer(Object.class, tcr);
		table.getTableHeader().setReorderingAllowed(false);
		table.getTableHeader().setResizingAllowed(false);
	    table.getColumnModel().getColumn(0).setPreferredWidth(80);
	    table.getColumnModel().getColumn(1).setPreferredWidth(80);
	    table.getColumnModel().getColumn(2).setPreferredWidth(80);
	    table.getColumnModel().getColumn(3).setPreferredWidth(10);
		scrollPane.setViewportView(table);
		
		factory = new _14211457_王耀_4_EmployeeFactory();
		factory.init();
		JOptionPane.showMessageDialog(
				null, 
				"为方便助教验收，程序已生成 10 个随机类型的员工。", 
				"提示",
				JOptionPane.INFORMATION_MESSAGE); 
		refresh();
	}
	
	private void CreateEmployee(int type){
		_14211457_王耀_4_InputEmployee input = new _14211457_王耀_4_InputEmployee(this, factory);
		input.SetTypeSelect(type);
		input.setVisible(true);
		input.setLocationRelativeTo(null); 
		frame.setEnabled(false);
	}

}
