package homework7;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JLabel;

import java.awt.Font;

import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.DefaultComboBoxModel;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.WindowEvent;
import java.awt.event.WindowAdapter;

public class _14211457_王耀_7_AddBookUI extends JFrame {

	private static final long serialVersionUID = 1L;
	private JPanel contentPane;
	private JTextField bookNameField;
	private JComboBox<String> bookTypeField;
	private JTextField isbnField;
	private JTextField bookPriceField;
	private JButton button;
	private JButton button_1;
	private _14211457_王耀_7_BooksUI parent;
	private JLabel label_3;
	private boolean editMode;
	private _14211457_王耀_7_BookSpecification tempBookInEditMode;

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
	
	public void setChange(_14211457_王耀_7_BookSpecification book){
		tempBookInEditMode = book;
		editMode = true;
		label_3.setText("修改书籍");
		button.setText("确认修改");
		bookNameField.setText(book.getTitle());
		bookPriceField.setText(book.getPrice() +"");
		bookTypeField.setSelectedIndex(book.getType()-1);
		isbnField.setText(book.getIsbn());
	}

	public _14211457_王耀_7_AddBookUI(_14211457_王耀_7_BooksUI parentUI) {
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				parent.setEnabled(true);
			}
		});
		editMode = false;
		parent = parentUI;
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setBounds(100, 100, 450, 300);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JLabel label = new JLabel("书籍名称");
		label.setFont(new Font("微软雅黑", Font.PLAIN, 15));
		label.setBounds(76, 63, 61, 26);
		contentPane.add(label);
		
		bookNameField = new JTextField();
		bookNameField.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		bookNameField.setBounds(147, 63, 217, 26);
		contentPane.add(bookNameField);
		bookNameField.setColumns(10);
		
		isbnField = new JTextField();
		isbnField.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		isbnField.setColumns(10);
		isbnField.setBounds(147, 135, 217, 26);
		contentPane.add(isbnField);
		
		JLabel lblIsbn = new JLabel("ISBN号");
		lblIsbn.setFont(new Font("微软雅黑", Font.PLAIN, 15));
		lblIsbn.setBounds(76, 135, 61, 26);
		contentPane.add(lblIsbn);
		
		JLabel label_1 = new JLabel("书籍类型");
		label_1.setFont(new Font("微软雅黑", Font.PLAIN, 15));
		label_1.setBounds(76, 99, 61, 26);
		contentPane.add(label_1);
		
		JLabel label_2 = new JLabel("书籍价格");
		label_2.setFont(new Font("微软雅黑", Font.PLAIN, 15));
		label_2.setBounds(76, 172, 61, 26);
		contentPane.add(label_2);
		
		bookPriceField = new JTextField();
		bookPriceField.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		bookPriceField.setColumns(10);
		bookPriceField.setBounds(147, 172, 190, 26);
		contentPane.add(bookPriceField);
		
		JLabel label_4 = new JLabel("元");
		label_4.setFont(new Font("微软雅黑", Font.PLAIN, 15));
		label_4.setBounds(347, 171, 17, 26);
		contentPane.add(label_4);
		
		button = new JButton("确认添加");
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String name = bookNameField.getText();
				int type = bookTypeField.getSelectedIndex() + 1;
				float price;
				String isbn = isbnField.getText();
				String priceText = bookPriceField.getText();
				if (type < 1 || type > 5){
					ErrorDia("您尚未为新书选择一种合法的类型");
					return;
				}
				try{
					price = Float.parseFloat(priceText);
				} catch (Exception e1){
					ErrorDia("您输入的价格不合法！");
					return;
				}
				_14211457_王耀_7_BookSpecification book = _14211457_王耀_7_Controller.getInstance().getBook(isbn);
				if ((! editMode && book != null) ||
					(editMode && book!=null && !isbn.equals(tempBookInEditMode.getIsbn()))){
					ErrorDia("已存在 ISBN 号为 " + isbn + " 的书籍《" + book.getTitle() + "》，"
							+ "请核对您的输入！");
					return;
				}
				if (!editMode){
					_14211457_王耀_7_BookSpecification newBook = new _14211457_王耀_7_BookSpecification(isbn, price, name, type);
					_14211457_王耀_7_Controller.getInstance().AddBook(newBook);
				} else if (tempBookInEditMode != null){
					tempBookInEditMode.setISBN(isbn);
					tempBookInEditMode.setPrice(price);
					tempBookInEditMode.setType(type);
					tempBookInEditMode.setTitle(name);
					_14211457_王耀_7_Controller.getInstance().updateSale();
				}
				_14211457_王耀_7_Controller.getInstance().updateBook();
				close();
			}
		});
		button.setFont(new Font("微软雅黑", Font.PLAIN, 15));
		button.setBounds(100, 208, 105, 31);
		contentPane.add(button);
		
		button_1 = new JButton("返回图书管理");
		button_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				close();
			}
		});
		button_1.setFont(new Font("微软雅黑", Font.PLAIN, 15));
		button_1.setBounds(218, 208, 130, 31);
		contentPane.add(button_1);
		
		bookTypeField = new JComboBox<String>();
		bookTypeField.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		bookTypeField.setModel(new DefaultComboBoxModel<String>(new String[] {"非教材类计算机图书", "教材类图书", "连环画类图书", "养生类图书", "其他"}));
		bookTypeField.setBounds(147, 99, 217, 26);
		contentPane.add(bookTypeField);
		
		label_3 = new JLabel("添加书籍");
		label_3.setFont(new Font("微软雅黑", Font.BOLD, 22));
		label_3.setBounds(166, 26, 94, 26);
		contentPane.add(label_3);
	}
}
