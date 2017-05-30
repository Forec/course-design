library ieee;
use ieee.std_logic_1164.all;

entity cpu is
	port(CLR, T3, C, Z: in std_logic;
		 RSWA, RSWB, RSWC: in std_logic;
		 -- RSWC/B/A is real signals from pins.
		 W3, W2, W1: in std_logic;
		 IR: in std_logic_vector(3 downto 0);
		 LDZ, LDC, CIN, DRW: out std_logic;
		 S, SEL: out std_logic_vector(3 downto 0);
		 M, ABUS, SBUS, MBUS: out std_logic;
		 PCINC, PCADD, ARINC, LPC, LAR, STOP, SELCTL: out std_logic;
		 LONG, SHORT, LIR, MEMW: out std_logic
		 --IsLight: out std_logic	-- test value
		);
end entity;

architecture workbench of cpu is
signal ADD, SUB, SigAND, SigOR, SigXOR, LD, ST, CCLR, SET,
	   INC, JC, JZ, JMP, SigOUT, CMP, STP: std_logic;
	   -- 16 instructions' flags
signal STO, SSTO: std_logic;
	   -- use SSTO as a flag to set STO
signal SWC, SWB, SWA: std_logic;
	   -- temp variables, store SWC/B/A for current process
signal SySW: std_logic;
	   -- use SySW as a flag to synchronizate SWC/B/A
begin
	
	process(SWC, SWB, SWA, IR, STO)
	-- set flags for different instructions according to SWC/B/A, IR and STO
	begin
		ADD <= '0'; SUB <= '0'; SigAnd <= '0'; SigOR <= '0'; 
		SigXOR <= '0'; LD <= '0'; ST <= '0'; CCLR <= '0'; 
		SET <= '0'; INC <= '0'; JC <= '0'; JZ <= '0'; JMP <= '0';
		SigOUT <= '0'; CMP <= '0'; STP <= '0';
		-- must set initial value, else all flags will be 1 at the beginning
		if (SWC = '0' and SWB = '0' and SWA = '0' and STO = '1') then
			case IR is							--  instructions    bits
				when "0000" => ADD <= STO;		--      add         0000
				when "0001" => SUB <= STO;		--      sub         0001
				when "0010" => SigAnd <= STO;	--		and			0010
				when "0011" => SigOR <= STO;	--		or			0011
				when "0100" => SigXOR <= STO;	--		xor			0100
				when "0101" => LD <= STO;		--		ld			0101
				when "0110" => ST <= STO;		--		st			0110
				when "0111" => CCLR <= STO;		--		clr			0111
				when "1000" => SET <= STO;		--		set			1000
				when "1001" => INC <= STO;		--		inc			1001
				when "1010" => JC <= STO;		--		jc			1010
				when "1011" => JZ <= STO;		--		jz			1011
				when "1100" => JMP <= STO;		--		jmp			1100
				when "1101" => SigOut <= STO;	--		out			1101
				when "1110" => CMP <= STO;		--		cmp			1110
				when others => STP <= STO;		--		stp			1111
			end case;
		end if;
	end process;
	
	process(CLR, SSTO, SySW)
	-- to synchronizate SWC/B/A, convert STO, and clear the status
	begin
		-- CLR has top priority
		if (CLR = '0') then		-- if CLR signal received
			STO <= '0';			-- set STO to 0
			SWC <= '1'; SWB <= '1'; SWA <= '1';
			-- set SWC/B/A to "111", which is a prohibited statu, in order to set SySW
		else
		-- if no CLR signal received
			if (SySW'event and SySW = '1') then		
			-- synchronizate SWC/B/A if SySW is at the rising edge
				SWC <= RSWC; SWB <= RSWB; SWA <= RSWA;
			end if;
			if (SSTO'event and SSTO = '0') then
			-- convert STO to '1' if SSTO is at the falling edge
				STO <= '1';
			end if;
		end if;
	end process;
	
	process(T3, SWC, SWB, SWA, W1, W2, STO)
	begin
		if T3'event and T3 = '1' then
			LIR <= ((not SWC) and (not SWB) and (not SWA)) and 
		   ((w2 and (not STO)) or
			((ADD or SUB or SigAND or SigOR or SigXOR or CCLR or 
			 SET or INC or SigOUT or CMP) and W1) or
			 ((LD or ST or JMP) and W2) or
			 (JC and C and W2) or
			 (JZ and Z and W2) or
			 (JC and (not C) and W1) or
			 (JZ and (not Z) and W1));
		end if;
	end process;
	-- LIR is '1' if SWC/B/A is "000" at W2 with STO = '0' or
	--				 SWC/B/A is "000" at W1 with ADD/SUB/AND/OR/
	--							XOR/CLR/SET/INC/OUT/CMP at W1 or
	--				 SWC/B/A is "000" at W2 with JC(C)/JZ(Z) or
	--				 SWC/B/A is "000" at W1 with JC(~C)/JZ(~Z). 
	-- In order to make LIT earlier than PCINC, it must be effective at the raising T3.
	
	SSTO <= (((SWC and (not SWB) and (not SWA)) and W2 and (not STO)) or 
			 (((not SWC) and SWB and (not SWA)) and W1 and (not STO)) or 
			 (((not SWC) and (not SWB) and SWA) and W1 and (not STO)) or 
			 ((not SWC) and (not SWB) and (not SWA) and W2 and (not STO))
			 ) and T3;
	-- only explain the last line: if SWC/B/A = "000" and W2, 
	-- then load instructions into IR , 
	-- STO convert to '1' to execute instructions.
	LDZ <= ((not SWC) and (not SWB) and (not SWA) and W1) and 
		   (ADD or SUB or SigAND or INC or SigOR or SigXOR or CCLR or SET or CMP);
	-- LDZ is '1' if SWC/B/A = "000" at W1 with ADD/SUB/AND/OR/XOR/INC/CLR/SET/CMP. 
	LDC <= ((not SWC) and (not SWB) and (not SWA) and W1) and (ADD or SUB or INC or JMP);
	-- LDC is '1' if SWC/B/A = "000" at W1 with ADD/SUB/INC/JMP.
	CIN <= (not SWC) and (not SWB) and (not SWA) and W1 and ADD;
	-- CIN is '1' if SWC/B/A = "000" at W1 with ADD.
	DRW <= (SWC and (not SWB) and (not SWA) and (W1 or W2)) or 
		   ( ((not SWC) and (not SWB) and (not SWA)) and 
		     (((add or sub or sigand or sigor or sigxor or inc or CCLR or SET) and W1) or 
		      (ld and W2)));
	-- DRW is '1' if SWC/B/A = "100" at W1/W2 								   or
	--               SWC/B/A = "000" at W1 with ADD/SUB/AND/OR/XOR/INC/CLR/SET or
	--               SWC/B/A = "000" at W2 with LD.
	M <= (not SWC) and (not SWB) and (not SWA) and 
		 (((sigand or sigor or sigxor or ld or st or cclr or set or jmp or sigout) and W1) or (st and W2));
	-- M is '1' if SWC/B/A = "000" at W1 with AND/OR/XOR/LD/ST/CLR/SET/JMP/OUT or
	--			   SWC/B/A = "000" at W2 with ST.
	ABUS <= (not SWC) and (not SWB) and (not SWA) and 
			(((add or sub or sigand or sigor or sigxor or ld or 
			   st or Cclr or set or inc or jmp or SigOUT) and w1) or 
			 (st and w2)
			 );
	-- ABUS is '1' if SWC/B/A is "000" at W1 with ADD/SUB/AND/OR/XOR/
	--										LD/ST/CLR/SET/INC/JMP/OUT or
	--				   SWC/B/A is "000" at W2 with ST.
	SBUS <= ((SWC and (not SWB) and (not SWA)) and (W1 or W2)) or 
			((not SWC) and SWB and (not SWA) and (not STO) and W1) or 
			((not SWC) and (not SWB) and SWA and W1) or 
			((not SWC) and (not SWB) and (not SWA) and (not STO) and W1);
	-- SBUS is '1' if SWC/B/A is "100" at W1/W2 			 or
	-- 				   SWC/B/A is "010" at W1 with STO = '0'or
	--				   SWC/B/A is "001" at W1 				 or
	--				   SWC/B/A is "000" at W1 with STO = '0'.
	MBUS <= ((not SWC) and SWB and (not SWA) and sto and w1) or 
		    ((not SWC) and (not SWB) and (not SWA) and ld and w2);
	-- MBUS is '1' if SWC/B/A is "010" at W1 with STO = '1' or
	--				   SWC/B/A is "000" at W2 with LD.
	PCINC <= ((not SWC) and (not SWB) and (not SWA)) and 
		     ((w2 and (not STO)) or
			  ((ADD or SUB or SigAND or SigOR or SigXOR or CCLR or 
			   SET or INC or SigOUT or CMP) and W1) or
			   ((LD or ST or JMP) and W2) or
			   (JC and C and W2) or
			   (JZ and Z and W2) or
			   (JC and (not C) and W1) or
			   (JZ and (not Z) and W1));
	-- PCINC is '1' if SWC/B/A is "000" at W2 with STO = '0' or
	--				 SWC/B/A is "000" at W1 with ADD/SUB/AND/OR/
	--							XOR/CLR/SET/INC/OUT/CMP at W1 or
	--				 SWC/B/A is "000" at W2 with JC(C)/JZ(Z) or
	--				 SWC/B/A is "000" at W1 with JC(~C)/JZ(~Z). 
	PCADD <= (not SWC) and (not SWB) and (not SWA) and ((jc and c) or (jz and z)) and w1; 
	-- PCADD is '1' if SWC/B/A is "000" at W2 with JC(C)/JZ(Z).
 	LPC <= ((not SWC) and (not SWB) and (not SWA) and jmp and w1) or 
		   ((not SWC) and (not SWB) and (not SWA) and w1 and (not STO));
	-- LPC is '1' if SWC/B/A is "000" at W1 with JMP or
	--				   SWC/B/A is "000" at W1 with STO = '0'.
	LAR <= ((not SWC) and SWB and (not SWA) and (not sto) and w1) or 
		   ((not SWC) and (not SWB) and SWA and w1 and (not STO)) or 
		   ((not SWC) and (not SWB) and (not SWA) and w1 and (ld or st));
	-- LAR is '1' if SWC/B/A is "010" at W1 with STO = '0' or
	--                  SWC/B/A is "001" at W1 with STO = '0' or
	--                  SWC/B/A is "000" at W1 with LD/ST.
	ARINC <= ((not SWC) and SWB and (not SWA) and sto and w1) or 
			 ((not SWC) and (not SWB) and SWA and sto and w1);
	-- ARINC is '1' if SWC/B/A is "010" at W1 with STO = '1' or
	--				    SWC/B/A is "001" at W1 with STO = '1'.
	STOP <= (SWC and (not SWB) and (not SWA)) or 
			((not SWC) and SWB and SWA) 	   or 
			((not SWC) and SWB and (not SWA)) or 
			((not SWC) and (not SWB) and SWA) or 
			((not SWC) and (not SWB) and (not SWA) and 
			 (((not STO) and W1) or (STO and STP and W1))
			 );
	-- STOP is '1' if SWC/B/A is "100" or "011" or "010" or "001" or 
	--				   SWC/B/A is "000" at W1 with STO = '0'       or
	--				   SWC/B/A is "000" at W1 with STO = '1' and STP = '1'.
	SELCTL <= (((SWC and (not SWB) and (not SWA)) or 
				((not SWC) and SWB and SWA)) and (W1 or W2)) or 
			  ((((not SWC) and SWB and (not SWA)) or 
			    ((not SWC) and (not SWB) and SWA)) and W1) or 
			  ((not SWC) and (not SWB) and (not SWA) and W1 and (not STO));
	-- SELCTL is '1' if SWC/B/A is ["100" or "011"] at W1/W2 or
	-- 				 	 SWC/B/A is ["010" or "001"] at W1    or
	--				 	 SWC/B/A is "000" at W1 with STO = '0'.
	LONG <= '0';
	-- LONG is always 0 because no W3 needed.
	SHORT <= ((not SWC) and (not SWB) and SWA and W1) or 
			 ((not SWC) and SWB and (not SWA) and W1) or
			 ((not SWC) and (not SWB) and (not SWA) and 
			   (W1 and (ADD or SUB or SigAND or SigOR or SigXOR or CCLR or CMP or
			    SET or INC or (JC and (not C)) or (JZ and (not Z)) or SigOUT)));
	-- SHORT is '1' if SWC/B/A is "001" at W1 or
	--				   SWC/B/A is "010" at W1 or
	--				   SWC/B/A is "000" at W1 with STO = '0' or
	--				   SWC/B/A is "000" at W1 with ADD/SUB/AND/OR/XOR/CLR/
	--									SET/INC/OUT/CMP/JC(~C)/JZ(~Z).

	MEMW <= ((not SWC) and (not SWB) and SWA and sto and w1) or 
			((not SWC) and (not SWB) and (not SWA) and st and w2);
	-- MEMW is '1' if SWC/B/A is "001" at W1 with STO = '1' or
	--				   SWC/B/A is "000" at W2 with ST.
	S(3) <= ((not SWC) and (not SWB) and (not SWA)) and 
			((W1 and (ADD or SigAND or SigOR or LD or ST or SET or JMP or SigOUT)) or 
			 (ST and W2)
			 );
	-- S(3) is '1' if SWC/B/A is "000" at W1 with ADD/AND/OR/LD/ST/SET/JMP/OUT or
	--				   SWC/B/A is "000" at W2 with ST.
	S(2) <= ((not SWC) and (not SWB) and (not SWA) and W1) and 
			(SUB or SigOR or SigXOR or ST or SET or JMP or CMP);
	-- S(2) is '1' if SWC/B/A is "000" at W1 with SUB/OR/XOR/ST/SET/JMP/CMP.
	S(1) <= ((not SWC) and (not SWB) and (not SWA)) and 
			((W1 and (SUB or SigAND or SigOR or SigXOR or 
			  LD or ST or CCLR or JMP or SigOUT or CMP)) or 
			  (ST and W2)
			 );
	-- S(1) is '1' if SWC/B/A is "000" at W1 with SUB/AND/OR/XOR/LD/ST/CLR/JMP/OUT/CMP or
	--				   SWC/B/A is "000" at W2 with ST.
	S(0) <= (not SWC) and (not SWB) and (not SWA) and 
			(ADD or SigAND or ST or CCLR or JMP) and W1;
	-- S(0) is '1' if SWC/B/A is "000" at W1 with ADD/AND/ST/CLR/JMP.
 	SEL(3) <= ((SWC and (not SWB) and (not SWA) and STO) and (W1 or W2)) or 
			  ((not SWC) and SWB and SWA and W2);
	-- SEL(3) is '1' if SWC/B/A is "100" at W1/W2 with STO = '1' or
	--					 SWC/B/A is "011" at W2.
	SEL(2) <= (SWC and (not SWB) and (not SWA) and W2);
	-- SEL(2) is '1' if SWC/B/A is "100" at W2.
	SEL(1) <= (SWC and (not SWB) and (not SWA) and (not STO) and W1) or 
			  (SWC and (not SWB) and (not SWA) and STO and W2)       or 
			  ((not SWC) and SWB and SWA and W2);
	-- SEL(1) is '1' if SWC/B/A is "100" at W1 with STO = '0' or
	--					SWC/B/A is "100" at W2 with STO = '1' or
	--					SWC/B/A is "011" at W2.
	SEL(0) <= (SWC and (not SWB) and (not SWA) and (not STO) and W1) or 
			  (SWC and (not SWB) and (not SWA) and STO and W1)       or 
			  ((not SWC) and SWB and SWA and (W1 or W2));
	-- SEL(0) is '1' if SWC/B/A is "100" at W1 with STO = '0' or
	--					SWC/B/A is "100" at W1 with STO = '1' or
	--					SWC/B/A is "011" at W1/W2.
	SySW <= SWC and SWB and SWA and W1;
	-- SySW is '1' is SWC/B/A is at prohibited statu.
	--IsLIght <= ?;
end workbench;
