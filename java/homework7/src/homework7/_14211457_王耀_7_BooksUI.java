package homework7;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.JLabel;

import java.awt.Font;
import java.awt.event.WindowEvent;

import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JButton;
import javax.swing.JTable;
import javax.swing.ListSelectionModel;
import javax.swing.SwingConstants;

import java.awt.event.WindowAdapter;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.text.DecimalFormat;
import java.awt.Toolkit;

public class _14211457_王耀_7_BooksUI extends JFrame {

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
	
	class BooksUIObserver implements _14211457_王耀_7_Observer{
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
	
	public _14211457_王耀_7_BooksUI(_14211457_王耀_7_mainUI parentUI) {
		setTitle("图书管理");
		setIconImage(Toolkit.getDefaultToolkit().getImage(_14211457_王耀_7_BooksUI.class.getResource("/javax/swing/plaf/metal/icons/ocean/directory.gif")));
		observer = new BooksUIObserver();
		_14211457_王耀_7_BookManager.getInstance().registerObserver(observer);
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				parent.getFrame().setEnabled(true);
				_14211457_王耀_7_BookManager.getInstance().removeObserver(observer);
			}
		});
		this.setResizable(false);
		parent = parentUI;
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setBounds(100, 100, 570, 323);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JLabel label = new JLabel("图书管理");
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
				"ISBN\u53F7", "\u540D\u79F0", "\u56FE\u4E66\u7C7B\u578B", "\u4EF7\u683C"
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
		scrollPane.setViewportView(table);
		
		JButton button = new JButton("添加新图书");
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				changeToNewBook(null);
			}
		});
		button.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		button.setBounds(60, 239, 104, 34);
		contentPane.add(button);
		
		JButton button_1 = new JButton("返回主界面");
		button_1.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		button_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				close();
			}
		});
		button_1.setBounds(434, 239, 109, 34);
		contentPane.add(button_1);
		
		JButton button_2 = new JButton("删除选中图书");
		button_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				int selectedRow = table.getSelectedRow();
				if (selectedRow < 0){
					ErrorDia("您尚未选中任何图书！");
					return;
				}
				_14211457_王耀_7_NoEditTableModel model = (_14211457_王耀_7_NoEditTableModel) table.getModel();
				String isbn = (String) model.getValueAt(selectedRow, 0);
				_14211457_王耀_7_BookSpecification book = _14211457_王耀_7_Controller.getInstance().getBook(isbn);
				boolean success = _14211457_王耀_7_Controller.getInstance().RemoveBook(isbn);
				if (success == true || book != null){
					_14211457_王耀_7_Controller.getInstance().updateBook();
					_14211457_王耀_7_Controller.getInstance().clearShopBook(book);
					_14211457_王耀_7_Controller.getInstance().updateSale();
					SuccessDia("您选中的图书 《" + book.getTitle() + "》（ISBN编号 " +
					book.getIsbn() + "）已被删除。");
				} else {
					ErrorDia("删除失败，您未选中图书或选中图书异常。");
				}
			}
		});
		button_2.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		button_2.setBounds(304, 239, 120, 34);
		contentPane.add(button_2);
		
		JButton button_3 = new JButton("编辑选中图书");
		button_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				int selectedRow = table.getSelectedRow();
				if (selectedRow < 0){
					ErrorDia("您尚未选中任何图书！");
					return;
				}
				_14211457_王耀_7_NoEditTableModel model = (_14211457_王耀_7_NoEditTableModel) table.getModel();
				String isbn = (String) model.getValueAt(selectedRow, 0);
				changeToNewBook(_14211457_王耀_7_BookManager.getInstance().getBook(isbn));
			}
		});
		button_3.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		button_3.setBounds(174, 239, 120, 34);
		contentPane.add(button_3);
		_14211457_王耀_7_Controller.getInstance().updateBook();
	}
	
	private void changeToNewBook(_14211457_王耀_7_BookSpecification book){
		_14211457_王耀_7_AddBookUI addBookUI = new _14211457_王耀_7_AddBookUI(this);
		if (book != null){
			addBookUI.setChange(book);
		}
		addBookUI.setVisible(true);
		addBookUI.setLocationRelativeTo(null);
		this.setEnabled(false);
	}
}
