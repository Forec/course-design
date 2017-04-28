package homework7;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JMenuBar;
import javax.swing.JMenu;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.ListSelectionModel;
import javax.swing.JLabel;
import javax.swing.JSpinner;
import javax.swing.JButton;
import javax.swing.SwingConstants;
import javax.swing.UIManager;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.Font;

import javax.swing.ImageIcon;
import javax.swing.SpinnerNumberModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.plaf.FontUIResource;
import javax.swing.table.DefaultTableCellRenderer;

import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.text.DecimalFormat;
import java.awt.Toolkit;

public class _14211457_王耀_7_mainUI {

	private JFrame frame;
	private JTable table;
	private _14211457_王耀_7_Observer observer;
	private _14211457_王耀_7_ShopCartUI shopCartUI;
	private JSpinner spinner;
	private JLabel bookChosed;
	
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					UIManager.put("OptionPane.buttonFont", new FontUIResource(new Font("微软雅黑", Font.PLAIN, 14)));
					UIManager.put("OptionPane.messageFont", new FontUIResource(new Font("微软雅黑", Font.PLAIN, 14)));
					_14211457_王耀_7_Controller.getInstance().random();
					_14211457_王耀_7_mainUI window = new _14211457_王耀_7_mainUI();
					window.frame.setLocationRelativeTo(null); 
					window.frame.setVisible(true);
					window.frame.setResizable(false);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}
	
	private void ErrorDia(String succmsg){
		JOptionPane.showMessageDialog(
				null, 
				succmsg, 
				"错误！", 
				JOptionPane.ERROR_MESSAGE); 
	}
	
	private void SuccessDia(String succmsg){
		JOptionPane.showMessageDialog(
				null, 
				succmsg, 
				"操作成功", 
				JOptionPane.PLAIN_MESSAGE); 
	}
	
	class MainUIObserver implements _14211457_王耀_7_Observer{
		public void update(){
			_14211457_王耀_7_NoEditTableModel model = (_14211457_王耀_7_NoEditTableModel) table.getModel();
		    if (model.getRowCount() > 0) {
		        for (int i = model.getRowCount() - 1; i > -1; i--) {
		            model.removeRow(i);
		        }
		    }
		    for (_14211457_王耀_7_BookSpecification b: _14211457_王耀_7_BookManager.getInstance().getBooks()){
				model.addRow(new Object[]{
						b.getIsbn(), 
						b.getTitle(), 
						b.getTypeName(),
						new DecimalFormat(".00").format(b.getPrice())});
			}
		}
	}
	
	public JFrame getFrame(){
		return frame;
	}

	public void clearShopCartUI(){
		shopCartUI = null;
	}
	
	public _14211457_王耀_7_mainUI() {
		observer = new MainUIObserver();
		_14211457_王耀_7_BookManager.getInstance().registerObserver(observer);
		initialize();
	}

	private void initialize() {
		shopCartUI = null;
		frame = new JFrame();
		frame.setTitle("模拟图书购物系统");
		frame.setIconImage(Toolkit.getDefaultToolkit().getImage(_14211457_王耀_7_mainUI.class.getResource("/javax/swing/plaf/metal/icons/ocean/computer.gif")));
		observer = new MainUIObserver();
		frame.addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				_14211457_王耀_7_BookManager.getInstance().removeObserver(observer);
			}
		});
		frame.setBounds(100, 100, 642, 401);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		JMenuBar menuBar = new JMenuBar();
		frame.setJMenuBar(menuBar);
		
		JMenu addMenu = new JMenu("管理");
		addMenu.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		menuBar.add(addMenu);
		
		JMenuItem addBook = new JMenuItem("图书管理");
		addBook.setIcon(new ImageIcon(_14211457_王耀_7_mainUI.class.getResource("/com/sun/java/swing/plaf/windows/icons/Directory.gif")));
		addBook.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		addBook.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				changeToBookUI();
			}
		});
		addMenu.add(addBook);
		
		JMenuItem addStrategy = new JMenuItem("策略管理");
		addStrategy.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				changeToStrategiesUI();
			}
		});
		addStrategy.setIcon(new ImageIcon(_14211457_王耀_7_mainUI.class.getResource("/com/sun/javafx/scene/web/skin/IncreaseIndent_16x16_JFX.png")));
		addStrategy.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		addMenu.add(addStrategy);
		
		JMenu menu = new JMenu("购物车");
		menu.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		menuBar.add(menu);
		
		JMenuItem menuItem = new JMenuItem("我的购物车");
		menuItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				openShoppingCart();
			}
		});
		
		JMenuItem menuItem_2 = new JMenuItem("加入购物车");
		menuItem_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				AddToShoppingCart();
			}
		});
		menuItem_2.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		menuItem_2.setIcon(new ImageIcon(_14211457_王耀_7_mainUI.class.getResource("/javax/swing/plaf/metal/icons/ocean/expanded.gif")));
		menu.add(menuItem_2);
		menuItem.setIcon(new ImageIcon(_14211457_王耀_7_mainUI.class.getResource("/javax/swing/plaf/metal/icons/ocean/upFolder.gif")));
		menuItem.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		menu.add(menuItem);
		
		JMenuItem menuItem_1 = new JMenuItem("清空购物车");
		menuItem_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String[] options = {"确定清空", "取消操作"};
				int Clear = JOptionPane.showOptionDialog(null, "即将清空您的购物车，此操作不可逆！请确认您的操作！",
						"确认您的选择",JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, 
						null, options, options[0]);
				if (Clear == JOptionPane.YES_OPTION){		// 确定
					_14211457_王耀_7_Controller.getInstance().clearShopCart();
					SuccessDia("您的购物车已经被清空！");
				}
			}
		});
		menuItem_1.setIcon(new ImageIcon(_14211457_王耀_7_mainUI.class.getResource("/com/sun/javafx/scene/web/skin/Redo_16x16_JFX.png")));
		menuItem_1.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		menu.add(menuItem_1);
		frame.getContentPane().setLayout(null);
		
		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setBounds(10, 24, 606, 226);
		frame.getContentPane().add(scrollPane);
		
		table = new JTable();
		table.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		table.setModel(new _14211457_王耀_7_NoEditTableModel(
			new Object[][] {
			},
			new String[] {
				"ISBN\u53F7", "\u540D\u79F0", "\u7C7B\u578B", "\u4EF7\u683C"
			}
		));
		table.setSelectionMode(ListSelectionModel.SINGLE_SELECTION); 
		DefaultTableCellRenderer tcr = new DefaultTableCellRenderer();
		tcr.setHorizontalAlignment(SwingConstants.CENTER);
		table.setDefaultRenderer(Object.class, tcr);
		table.getTableHeader().setReorderingAllowed(false);
		table.getTableHeader().setResizingAllowed(false);
	    table.getColumnModel().getColumn(0).setPreferredWidth(100);
	    table.getColumnModel().getColumn(1).setPreferredWidth(100);
	    table.getColumnModel().getColumn(2).setPreferredWidth(100);
	    table.getColumnModel().getColumn(3).setPreferredWidth(20);
        table.getSelectionModel().addListSelectionListener(new ListSelectionListener(){
            public void valueChanged(ListSelectionEvent e) {
            	boolean bl=e.getValueIsAdjusting();
            	if(!bl){
            		int selectedRow = table.getSelectedRow();
            		if (selectedRow < 0){
            			bookChosed.setText("您尚未选中任何图书");
            		}else {
	            		_14211457_王耀_7_NoEditTableModel model = (_14211457_王耀_7_NoEditTableModel) table.getModel();
	            		bookChosed.setText("当前选中图书：《" +
	            				(String) model.getValueAt(selectedRow, 1) + "》");
            		}
            	}                
            }
        });
		scrollPane.setViewportView(table);
		
		bookChosed = new JLabel("您尚未选中任何图书");
		bookChosed.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		bookChosed.setBounds(10, 260, 374, 30);
		frame.getContentPane().add(bookChosed);
		
		JLabel label = new JLabel("购买数量");
		label.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		label.setBounds(473, 260, 65, 31);
		frame.getContentPane().add(label);
		
		JLabel label_1 = new JLabel("本");
		label_1.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		label_1.setBounds(599, 268, 17, 15);
		frame.getContentPane().add(label_1);
		
		spinner = new JSpinner();
		spinner.setModel(new SpinnerNumberModel(new Integer(0), new Integer(0), null, new Integer(1)));
		spinner.setBounds(541, 260, 54, 30);
		frame.getContentPane().add(spinner);
		
		JButton addToCartButton = new JButton("加入购物车");
		addToCartButton.setIcon(new ImageIcon(_14211457_王耀_7_mainUI.class.getResource("/javax/swing/plaf/metal/icons/ocean/expanded.gif")));
		addToCartButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				AddToShoppingCart();
			}
		});
		addToCartButton.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		addToCartButton.setBounds(331, 301, 127, 30);
		frame.getContentPane().add(addToCartButton);
		
		JButton viewCartButton = new JButton("查看购物车");
		viewCartButton.setIcon(new ImageIcon(_14211457_王耀_7_mainUI.class.getResource("/javax/swing/plaf/metal/icons/ocean/homeFolder.gif")));
		viewCartButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				openShoppingCart();
			}
		});
		viewCartButton.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		viewCartButton.setBounds(468, 301, 127, 30);
		frame.getContentPane().add(viewCartButton);
		_14211457_王耀_7_BookManager.getInstance().registerObserver(observer);
		_14211457_王耀_7_Controller.getInstance().updateBook();
		JOptionPane.showMessageDialog(
				null, 
				"为方便助教验收，程序初始化时已作业要求添加了指定的几个策略、图书以及购物记录。\n你可以"+
				"增加新的自定义策略或图书，也可以对策略/图书执行编辑/删除等操作。", 
				"友情提示", 
				JOptionPane.PLAIN_MESSAGE); 
	}
	
	private void changeToBookUI(){
		_14211457_王耀_7_BooksUI booksUI = new _14211457_王耀_7_BooksUI(this);
		booksUI.setVisible(true);
		booksUI.setLocationRelativeTo(null); 
		booksUI.setResizable(false);
		frame.setEnabled(false);
	}
	
	private void changeToStrategiesUI(){
		_14211457_王耀_7_StrategiesUI strategyUI = new _14211457_王耀_7_StrategiesUI(this);
		strategyUI.setVisible(true);
		strategyUI.setLocationRelativeTo(null); 
		strategyUI.setResizable(false);
		frame.setEnabled(false);
	}	
	
	private void openShoppingCart(){
		if (shopCartUI == null){
			shopCartUI = new _14211457_王耀_7_ShopCartUI(this);
			shopCartUI.setVisible(true);
			shopCartUI.setLocationRelativeTo(null); 
			shopCartUI.setResizable(false);
		}
	}	
	
	private void AddToShoppingCart(){
		int selectedRow = table.getSelectedRow();
		int copies;
		try{
			copies = (int) spinner.getValue();
		}catch (Exception e1){
			ErrorDia("您设置的购买数量有误！");
			return;
		}
		if (copies <= 0){
			ErrorDia("您设置的购买数量有误！");
			return;
		}
		if (selectedRow < 0){
			ErrorDia("您尚未选中任何图书！");
			return;
		}
		_14211457_王耀_7_NoEditTableModel model = (_14211457_王耀_7_NoEditTableModel) table.getModel();
		String isbn = (String) model.getValueAt(selectedRow, 0);
		_14211457_王耀_7_BookSpecification bookSpecification = _14211457_王耀_7_Controller.getInstance().getBook(isbn);
		if (bookSpecification == null){
			ErrorDia("未检索到您选择的书籍！添加失败！");
			return;
		}
		if (_14211457_王耀_7_Controller.getInstance().AddSaleItem(isbn, copies)){
			SuccessDia("您选择的《" + bookSpecification.getTitle() + "》（共 " +
						copies + " 本）已添加到购物车！");
			spinner.setValue(0);
		} else {
			ErrorDia("出现异常，添加失败！");
		}
	}
}
