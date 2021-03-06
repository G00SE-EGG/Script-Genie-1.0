SPOOL WWSA_CREATE_FSA_MANUAL_ADJUSTMENT_PSQ_.log

SET SERVEROUTPUT ON SIZE 1000000

DECLARE
  gc_user                               CONSTANT VARCHAR2(30) :='';
  gc_developer                          CONSTANT VARCHAR2(30) :='';
  gc_run_user                           CONSTANT VARCHAR2(30) := 'WWSA';  
  v_data_script_id                      NUMBER          :=0;
  v_data_log_id                         NUMBER          :=0;
  v_data_script_param_id                NUMBER          :=0;
  v_count                               NUMBER          :=0;
  v_count2                              NUMBER          :=0;
  v_count3                              NUMBER          :=0;
  v_count_adj_asso                      NUMBER          :=0;  
  v_count_adj                           NUMBER          :=0;
  v_script_name VARCHAR2 (100) := 'WWSA_CREATE_FSA_MANUAL_ADJUSTMENT_PSQ_.sql';
  lv_last_update_user                   VARCHAR2(30);  
  v_script_location                     CLOB            := '';
  v_psq_it_number                       NUMBER          :=;
  v_param_names                         CLOB            := '';
  v_table_names                         CLOB            := '';
  v_param_values                        CLOB            := ''; 
  v_comments                            CLOB            := 'Manual Adjustment';
  
 -- Adjustment status
  sc_AdjStatusSubmitted                 CONSTANT NUMBER := wwsa.sa_constants.gc_AdjStatusSubmitted;
  sc_AdjStatusProcessed                 CONSTANT NUMBER := wwsa.sa_constants.gc_AdjStatusProcessed;


         
  lv_adjustments_rec                    wwsa.sa_adjustments_tapi.row_type;
  lv_adjustment_details_rec             wwsa.sa_adjustment_details_tapi.row_type;
  p_adjustment_associated_txn_id        wwsa.sa_adj_associated_txns.adjustment_associated_txn_id%TYPE ;
  p_create_user                         wwsa.sa_adj_associated_txns.create_user%TYPE;
  rec_row                               wwsa.sa_adj_associated_txns_tapi.row_type;  
  
--PROCEDURE create_adj_detail_and_activity
  p_process_log_id                      wwsa.ops_process_logs.process_log_id%TYPE;
 
  v_employee_id                         wwsa.sa_adjustments.employee_id%TYPE;
  v_adjustment_id                       wwsa.sa_adjustments.adjustment_id%TYPE;
  v_transaction_type                    VARCHAR2(3);
  v_adj_amt_validation_rule_id          WWSA.SA_ADJUSTMENT_RULES.ADJ_AMT_VALIDATION_RULE_ID%TYPE;
  v_validation_value                    WWSA.SA_ADJUSTMENT_RULES.VALIDATION_VALUE%type;
  v_change_acct_bal_action_id           WWSA.SA_ADJUSTMENT_RULES.CHANGE_ACCT_BALANCE_ACTION_ID%type;    
  v_other_action_id                     WWSA.SA_ADJUSTMENT_RULES.OTHER_ACTION_ID%type;
  v_credit_member_account_id            WWSA.SA_ADJUSTMENTS.CREDIT_MEMBER_ACCOUNT_ID%type;
  v_debit_member_account_id             WWSA.SA_ADJUSTMENTS.DEBIT_MEMBER_ACCOUNT_ID%type;
  v_total_adjustment_amt                WWSA.SA_ADJUSTMENTS.TOTAL_ADJUSTMENT_AMT%type;
  v_associated_txn_selection_id         WWSA.SA_ADJUSTMENT_RULES.ASSOCIATED_TXN_SELECTION_ID%type;
  v_adj_amount_editable_flag            WWSA.SA_ADJUSTMENT_RULES.ADJ_AMOUNT_EDITABLE_FLAG%type;
  v_from_plan_desc_id                   WWSA.SA_ADJUSTMENT_RULES.FROM_PLAN_DESC_ID%type ;
  v_to_plan_desc_id                     WWSA.SA_ADJUSTMENT_RULES.TO_PLAN_DESC_ID%type;
  v_create_HSA_acct_track_flag          WWSA.SA_ADJUSTMENT_RULES.CREATE_HSA_ACCT_TRACK_FLAG%type;
  v_associated_txn_type_id              WWSA.SA_ADJUSTMENT_RULES.ASSOCIATED_TXN_TYPE_ID%type;

  
  lv_success_flag                       PLS_INTEGER;
  lv_process_message                    VARCHAR2(500);
  v_success_flag                        NUMBER;
  v_adjustment_type_id                  wwsa.sa_adjustment_types.adjustment_type_id%type ;
  
  v_process_message                     VARCHAR2(2000);    
  
BEGIN

  v_script_location  := v_script_location||v_script_name;
  lv_last_update_user :='SCRIPT-'||gc_developer||'-#'||v_psq_it_number;
  v_table_names :=UPPER ('wwsa.sa_activity_settled|wwsa.sa_activity_settled');
  
  DBMS_OUTPUT.PUT_LINE ('Begin - Script: '|| v_script_name ||' - '|| to_char(sysdate,'DD-MON-YYYY HH24:MI:SS')); 

  --BEGIN SCRIPT LOGGING
  --------------------------------------------------------------------------------------------------------------
  wwsa.ops_data_api.log_data_script_fix 
                (v_script_name
                ,v_script_location
                ,v_psq_it_number
                ,v_param_names
                ,v_table_names
                ,v_param_values
                ,v_comments
                ,gc_developer
                ,gc_run_user
                ,gc_user
                );  
		
 
            
  FOR rec_main 
  IN (select 3313133 employee_id, 44443222 debit_member_account_id, 12222334 credit_member_account_id,  NULL orig_card_txn_id, NULL orig_claim_id, NULL orig_pmp_instruction_id, 602 adjustment_type_id, 199.99 from dual union all
select 2442424 employee_id, 55553433 debit_member_account_id, 56778900 credit_member_account_id,  NULL orig_card_txn_id, NULL orig_claim_id, NULL orig_pmp_instruction_id, 406 adjustment_type_id, 2365.36 from  dual;
)

  LOOP    

     lv_adjustments_rec.adjustment_id            := NULL;
     lv_adjustments_rec.adjustment_type_id       := rec_main.adjustment_type_id;         
     lv_adjustments_rec.adjustment_reason_id     := NULL; 
     lv_adjustments_rec.total_adjustment_amt     := rec_main.total_adjustment_amt;
     lv_adjustments_rec.comments                 := 'Manual Adjustment PSQ#' || v_psq_it_number;                        
     lv_adjustments_rec.submitted_by             := lv_last_update_user;
     lv_adjustments_rec.employee_id              := rec_main.employee_id;
     lv_adjustments_rec.credit_member_account_id := rec_main.credit_member_account_id;
     lv_adjustments_rec.debit_member_account_id  := rec_main.debit_member_account_id;          
     lv_adjustments_rec.submitted_date           := SYSDATE;         
     lv_adjustments_rec.status_id                := sc_AdjStatusSubmitted; --394;  --processed        --393; --submitted
     lv_adjustments_rec.status_date              := SYSDATE;                     
     lv_adjustments_rec.create_user              := lv_last_update_user;
     lv_adjustments_rec.create_date              := SYSTIMESTAMP;                     
     lv_adjustments_rec.last_update_user         := lv_last_update_user;
     lv_adjustments_rec.last_update_date         := SYSTIMESTAMP; 

                        
      wwsa.sa_adjustments_tapi.insert_row (lv_adjustments_rec
                                      ,lv_success_flag
                                      ,lv_process_message
                                      );
              
      IF lv_success_flag = sa_constants.gc_false THEN
         RAISE_APPLICATION_ERROR(-20001, lv_process_message);      
      ELSE       
        v_count_adj := v_count_adj +1;         
      END IF;
                   
     commit;
     
     IF  rec_main.adjustment_type_id in (109,206,406) and (nvl(rec_main.orig_claim_id,0)<>0 or nvl(rec_main.orig_pmp_instruction_id,0)<>0 or nvl(rec_main.orig_card_txn_id,0)<>0)
     THEN
      p_adjustment_associated_txn_id :=NULL;
                  
      rec_row.adjustment_associated_txn_id       := p_adjustment_associated_txn_id;
      rec_row.adjustment_id                      := lv_adjustments_rec.adjustment_id; 
      rec_row.settlement_id                      := NULL;--rec_main.settlement_id;
      rec_row.claim_id                           := rec_main.orig_claim_id;
      rec_row.pmp_instruction_id                 := rec_main.orig_pmp_instruction_id;
      rec_row.card_transaction_id                := rec_main.orig_card_txn_id;
      rec_row.account_fee_id                     := NULL;
      rec_row.amount                             := rec_main.total_adjustment_amt;
      rec_row.create_user                        := lv_last_update_user;
      rec_row.create_date                        := SYSTIMESTAMP;
      rec_row.last_update_user                   := lv_last_update_user;
      rec_row.last_update_date                   := SYSTIMESTAMP;

      wwsa.sa_adj_associated_txns_tapi.insert_row
        (rec_row
        ,v_success_flag
        ,v_process_message);

      IF v_success_flag = 1 THEN
        p_adjustment_associated_txn_id := rec_row.adjustment_associated_txn_id;
        
        v_count_adj_asso := v_count_adj_asso +1;
        
      ELSE
        RAISE_APPLICATION_ERROR(-20001, v_process_message);
      END IF;         
     END IF;  

      SELECT 
         adj.employee_id                        
        ,adj.adjustment_id                     
        ,'ADJ'                                 
        ,adjr.adj_amt_validation_rule_id       
        ,adjr.validation_value                 
        ,adjr.change_acct_balance_action_id    
        ,adjr.other_action_id                  
        ,adj.credit_member_account_id          
        ,adj.debit_member_account_id           
        ,adj.total_adjustment_amt              
        ,adjr.associated_txn_selection_id      
        ,adjr.adj_amount_editable_flag         
        ,adjr.from_plan_desc_id                
        ,adjr.to_plan_desc_id                  
        ,adjr.create_HSA_acct_track_flag       
        ,adjr.associated_txn_type_id           
     INTO
         v_employee_id
        ,v_adjustment_id
        ,v_transaction_type
        ,v_adj_amt_validation_rule_id
        ,v_validation_value
        ,v_change_acct_bal_action_id
        ,v_other_action_id
        ,v_credit_member_account_id
        ,v_debit_member_account_id
        ,v_total_adjustment_amt
        ,v_associated_txn_selection_id
        ,v_adj_amount_editable_flag
        ,v_from_plan_desc_id
        ,v_to_plan_desc_id
        ,v_create_HSA_acct_track_flag
        ,v_associated_txn_type_id
     FROM  wwsa.sa_adjustments              adj
          ,wwsa.sa_adjustment_types         adtp
          ,wwsa.sa_adjustment_rules         adjr
    WHERE adj.adjustment_type_id = adtp.adjustment_type_id
      AND adj.adjustment_type_id = adjr.adjustment_type_id
      AND adj.employee_id         = rec_main.employee_id
      AND adj.status_id           = 393   -- submitted
      AND adj.adjustment_type_id  = rec_main.adjustment_type_id  
      AND adj.adjustment_id = lv_adjustments_rec.adjustment_id; 

    wwsa.sa_activity_api.create_adj_detail_and_activity
        (p_process_log_id                => null
        ,p_employee_id                   => v_employee_id
        ,p_adjustment_id                 => v_adjustment_id
        ,P_change_acct_bal_action_id     => v_change_acct_bal_action_id
        ,p_credit_member_account_id      => v_credit_member_account_id
        ,p_debit_member_account_id       => v_debit_member_account_id
        ,p_total_adjustment_amt          => v_total_adjustment_amt
        ,p_associated_txn_selection_id   => v_associated_txn_selection_id
        ,p_adj_amount_editable_flag      => v_adj_amount_editable_flag 
        ,p_from_plan_desc_id             => v_from_plan_desc_id
        ,p_to_plan_desc_id               => v_to_plan_desc_id
        ,p_create_HSA_acct_track_flag    => v_associated_txn_type_id
        );
  
       COMMIT;
       
        UPDATE wwsa.sa_adjustments adj
        SET adj.status_id = 394,
            adj.status_date = SYSDATE,
            adj.last_update_date = SYSDATE,
            adj.last_update_user = lv_last_update_user 
        WHERE adj.adjustment_id = v_adjustment_id;
              
        COMMIT;
       
      v_count2 := v_count2 + 1;
      
            
      
  END LOOP;
  
    DBMS_OUTPUT.PUT_LINE ('number of adjustments records created = '|| v_count_adj);
    DBMS_OUTPUT.PUT_LINE ('number of adjustments processed = '|| v_count2);
    DBMS_OUTPUT.PUT_LINE ('End - '|| lv_last_update_user  ||' - '|| to_char(sysdate,'DD-MON-YYYY HH24:MI:SS'));
 
EXCEPTION
WHEN OTHERS THEN
    ROLLBACK;
    DBMS_OUTPUT.PUT_LINE ('fatal error: '|| sqlerrm); 
END;
/
SPOOL OFF
