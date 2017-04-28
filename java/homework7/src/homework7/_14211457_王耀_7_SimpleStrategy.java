package homework7;
/**
 * Created by Forec on 2016/12/28.
 * 此类为简单策略的基类，任何简单策略可从此类拓展。例如本次作业要求的百分比折扣策略和
 * 绝对值折扣策略。
 */
public abstract class _14211457_王耀_7_SimpleStrategy extends _14211457_王耀_7_BasicStrategy {

    protected int strategyType;

    public int getStrategyType(){
        return strategyType;
    }
}
