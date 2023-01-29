using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class CalculatorBehavior : MonoBehaviour
{
    public Text textObj;
    private string formula;
    // Start is called before the first frame update
    void Start()
    {
        formula = "";
        GameObject ggg = GameObject.Find("Canvas/Background/Text");
        textObj = (Text)ggg.GetComponent<Text>();
        Debug.Log(textObj);
        for (int i = 1; i <= 9; i++)
        {
            GameObject btnObj_tmp = GameObject.Find("Canvas/Button_" + i);
            Button btn = (Button)btnObj_tmp.GetComponent<Button>();
            string a = i.ToString();
            btn.onClick.AddListener(delegate () {
                onClickInput(a);
            });
            Debug.Log(btn);
            Debug.Log(a);
        }

        GameObject hhh = GameObject.Find("Canvas/Button_plus");
        Button btnPlus = (Button)hhh.GetComponent<Button>();
        btnPlus.onClick.AddListener(delegate () {
            onClickInput("+");
        });

        GameObject iii = GameObject.Find("Canvas/Button_minus");
        Button btnMinus = (Button)iii.GetComponent<Button>();
        btnMinus.onClick.AddListener(delegate () {
            onClickInput("-");
        });

        GameObject jjj = GameObject.Find("Canvas/Button_del");
        Button btnDel = (Button)jjj.GetComponent<Button>();
        btnDel.onClick.AddListener(onClickDel);

        GameObject kkk = GameObject.Find("Canvas/Button_equal");
        Button btnEqual = (Button)kkk.GetComponent<Button>();
        btnEqual.onClick.AddListener(onClickEqual);
    }

    void onClickInput(string i)
    {
        Debug.Log(i);
        formula = formula + i;
        textObj.text = formula;
    }

    void onClickEqual()
    {
        bool flag = true;
        int ans = 0, last = 0, op = 1, length = 0;
        for (int i = 0; i < formula.Length; i++) {
            if (formula[i] == '+' || formula[i] == '-') {
                // avoid something like 1++4 
                if (length == 0 && i != 0) {
                    flag = false;
                    break;
                }
                
                // do math
                if (length != 0) {
                    int a = int.Parse(formula.Substring(last, length));
                    ans = ans + op * a;
                }

                // update operation
                op = 1;
                if (formula[i] == '-') op = -1;
            
                last = i + 1;
                length = 0;
                
            } else if (formula[i] == '=') {
                // should not exist any '=' in formula.
                flag = false;
                break;
            } else {
                // for numbers
                length ++;
            }
        }
        
        // last number to calculate
        if (length == 0)
            flag = false;
        else {
            int a = int.Parse(formula.Substring(last, length));
            ans += op * a;
        }

        // output if formula is correct
        if (flag) {
            formula = formula + "=" + ans.ToString();
            textObj.text = formula;
        }
        
    }

    void onClickDel()
    {
        if (formula.Length > 0)
        {
            formula = formula.Substring(0, formula.Length - 1);
            textObj.text = formula;
        }
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
