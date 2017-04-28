package homework7;

import javax.swing.table.DefaultTableModel;

class _14211457_王耀_7_NoEditTableModel extends DefaultTableModel {  
	private static final long serialVersionUID = 1L;
	public _14211457_王耀_7_NoEditTableModel(Object[][] data, Object[] columnNames) {  
        super(data, columnNames);
    }  
    public boolean isCellEditable(int row, int column) {  
        return false;
    }  
}  