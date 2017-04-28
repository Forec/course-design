package homework7;


import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.ListSelectionModel;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.JLabel;

import java.awt.Font;

import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JButton;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.WindowEvent;
import java.awt.event.WindowAdapter;
import java.text.DecimalFormat;
import java.awt.Toolkit;

public class _14211457_王耀_7_ShopCartUI extends JFrame {

	private static final long serialVersionUID = 1L;
	private JPanel contentPane;
	private JTable shopCartTable;
	private _14211457_王耀_7_Observer observer;
	private _14211457_王耀_7_mainUI parent;
	private JLabel cost;
	
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

	class ShopCartUIObserver implements _14211457_王耀_7_Observer{
		public void update(){
			_14211457_王耀_7_NoEditTableModel model = (_14211457_王耀_7_NoEditTableModel) shopCartTable.getModel();
		    if (model.getRowCount() > 0) {
		        for (int i = model.getRowCount() - 1; i > -1; i--) {
		            model.removeRow(i);
		        }
		    }
		    double total = 0;
		    for (_14211457_王耀_7_SaleLineItem s: _14211457_王耀_7_Controller.getInstance().getShoppingCart().getSaleLines()){
				model.addRow(new Object[]{
						s.getNumber() + "",
						s.getProdSpec().getTitle(),
						s.getProdSpec().getIsbn(),
						s.getCopies(),
						new DecimalFormat(".00").format(s.getSubTotal())
				});
				total += s.getSubTotal();
			}
		    cost.setText(new DecimalFormat(".00").format(total));
		}
	}
	
	public _14211457_王耀_7_ShopCartUI(_14211457_王耀_7_mainUI parentUI) {
		setIconImage(Toolkit.getDefaultToolkit().getImage(_14211457_王耀_7_ShopCartUI.class.getResource("/javax/swing/plaf/metal/icons/ocean/homeFolder.gif")));
		setTitle("购物车");
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				parent.clearShopCartUI();
			}
		});
		parent = parentUI;
		setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
		setBounds(100, 100, 569, 390);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		JLabel label = new JLabel("购物车");
		label.setFont(new Font("微软雅黑", Font.BOLD, 24));
		label.setBounds(234, 22, 89, 33);
		contentPane.add(label);
		
		JScrollPane scrollPane = new JScrollPane();
		scrollPane.setBounds(10, 73, 533, 223);
		contentPane.add(scrollPane);
		
		shopCartTable = new JTable();
		shopCartTable.setFont(new Font("微软雅黑", Font.PLAIN, 13));
		shopCartTable.setModel(new _14211457_王耀_7_NoEditTableModel(
			new Object[][] {
			},
			new String[] {
				"\u8BA2\u5355\u7F16\u53F7", "\u4E66\u7C4D\u540D\u79F0", "ISBN\u7F16\u53F7", "\u8D2D\u4E70\u6570\u91CF", "价格"
			}
		));
		shopCartTable.setSelectionMode(ListSelectionModel.SINGLE_SELECTION); 
		DefaultTableCellRenderer tcr = new DefaultTableCellRenderer();
		tcr.setHorizontalAlignment(SwingConstants.CENTER);
		shopCartTable.setDefaultRenderer(Object.class, tcr);
		shopCartTable.getTableHeader().setReorderingAllowed(false);
		shopCartTable.getTableHeader().setResizingAllowed(false);
		shopCartTable.getColumnModel().getColumn(0).setPreferredWidth(10);
		shopCartTable.getColumnModel().getColumn(1).setPreferredWidth(120);
		shopCartTable.getColumnModel().getColumn(2).setPreferredWidth(120);
		shopCartTable.getColumnModel().getColumn(3).setPreferredWidth(20);
		shopCartTable.getColumnModel().getColumn(4).setPreferredWidth(20);
		scrollPane.setViewportView(shopCartTable);
		
		observer = new ShopCartUIObserver();
		
		JButton button = new JButton("删除选中记录");
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				int selectedRow = shopCartTable.getSelectedRow();
				if (selectedRow < 0){
					ErrorDia("您尚未选中任何记录！");
					return;
				}
				_14211457_王耀_7_NoEditTableModel model = (_14211457_王耀_7_NoEditTableModel) shopCartTable.getModel();
				String saleLineNumberText = (String) model.getValueAt(selectedRow, 0);
				int saleLineNumber = -1;
				try{
					saleLineNumber = Integer.parseInt(saleLineNumberText);
				} catch (Exception e1){
					ErrorDia("您选中的记录格式不合法");
				}
				if (saleLineNumber != -1 &&_14211457_王耀_7_Controller.getInstance().RemoveSaleItem(saleLineNumber)){
					SuccessDia("您选中的记录已经删除成功！");
					_14211457_王耀_7_Controller.getInstance().updateSale();
				} else {
					ErrorDia("删除失败，您未选中任何购物记录或选中记录异常。");
				}
			}
		});
		button.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		button.setBounds(289, 307, 124, 34);
		contentPane.add(button);
		
		JButton button_1 = new JButton("关闭购物车");
		button_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				close();
			}
		});
		button_1.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		button_1.setBounds(423, 307, 120, 34);
		contentPane.add(button_1);
		
		JLabel label_1 = new JLabel("当前购物总金额：");
		label_1.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		label_1.setBounds(10, 306, 118, 35);
		contentPane.add(label_1);
		
		cost = new JLabel("0.00 元");
		cost.setFont(new Font("微软雅黑", Font.PLAIN, 14));
		cost.setBounds(123, 306, 68, 35);
		contentPane.add(cost);
		_14211457_王耀_7_Controller.getInstance().getShoppingCart().registerObserver(observer);
		observer.update();
	}
}
