#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void swap(int *num1,int *num2){
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

void bubble(char  Name[100][100], int *arr, int num){
	for(int i=0;i<num;i++){
		for(int j=0;j<num-i-1;j++){
			if(arr[j]>arr[j+1]){
				swap(&arr[j],&arr[j+1]);	
				char Temp[100];
				strcpy(Temp,Name[j]);
				strcpy(Name[j],Name[j+1]);
				strcpy(Name[j+1],Temp);	
			}
		}
	}
}

void fileSafe(char Name[100][100],char yn3,int *Total,float *Rr1,float *Rr2,float *Rr3,float *Rr4,float *Rr5,float *Rr6,int idx){
	if(yn3=='y'){
		FILE *fp = fopen("/Users/yong/Desktop/stockA/test.txt", "a");
		if(!fp) {
  			perror("檔案開啟失敗\n"); 
		}
		else{
			printf("儲存成功！\n");
			time_t now; // 變數宣告
			time(&now); // 取得現在的日期時間
			fprintf(fp,"\n%s\n",ctime(&now)); // 列印
			/*for(int i=0;i<idx;i++){
				fprintf(fp,"|%6s %12d|\n",Name[i],Total[i]);
			}*/
            fprintf(fp,"\n\n-------------------------------------------------------\n");
            fprintf(fp,"比較排序:\n");
            
            fprintf(fp,"--------------------------\n");
            bubble(Name,Total,idx);
            fprintf(fp,"|%7s  %15s|\n","Co.","TotalRank");
            fprintf(fp,"**************************\n");
            for(int i=0;i<idx;i++){
                fprintf(fp,"|%7s  %15d|\n",Name[i],Total[i]);
            }
            fprintf(fp,"--------------------------\n");
            bubble(Name,(int *)Rr1,idx);
            fprintf(fp,"|%7s  %15s|\n","Co.","CurrentRatio");
            fprintf(fp,"**************************\n");
            for(int i=0;i<idx;i++){
                fprintf(fp,"|%7s  %15.2f|\n",Name[i],Rr1[i]);
            }
            fprintf(fp,"--------------------------\n");
            bubble(Name,(int *)Rr2,idx);
            fprintf(fp,"|%7s  %15s|\n","Co.","DebtRatio");
            fprintf(fp,"**************************\n");
            for(int i=0;i<idx;i++){
                fprintf(fp,"|%7s  %15f.2|\n",Name[i],Rr2[i]);
            }
            fprintf(fp,"--------------------------\n");
            bubble(Name,(int *)Rr3,idx);
            fprintf(fp,"|%7s  %15s|\n","Co.","ReturnOnSales");
            fprintf(fp,"**************************\n");
            for(int i=0;i<idx;i++){
                fprintf(fp,"|%7s  %15.2f|\n",Name[i],Rr3[i]);
            }
            fprintf(fp,"--------------------------\n");
            bubble(Name,(int *)Rr4,idx);
            fprintf(fp,"|%7s  %15s|\n","Co.","ReturnOnEquity");
            fprintf(fp,"**************************\n");
            for(int i=0;i<idx;i++){
                fprintf(fp,"|%7s  %15.2f|\n",Name[i],Rr4[i]);
            }
            fprintf(fp,"--------------------------\n");
            bubble(Name,(int *)Rr5,idx);
            fprintf(fp,"|%7s  %15s|\n","Co.","RevenueGrowth");
            fprintf(fp,"**************************\n");
            for(int i=0;i<idx;i++){
                fprintf(fp,"|%7s  %15.2f|\n",Name[i],Rr5[i]);
            }
            fprintf(fp,"--------------------------\n");
            bubble(Name,(int *)Rr6,idx);
            fprintf(fp,"|%7s  %15s|\n","Co.","NetIncome");
            fprintf(fp,"**************************\n");
            for(int i=0;i<idx;i++){
                fprintf(fp,"|%7s  %15.2f|\n",Name[i],Rr6[i]);
            }
            fprintf(fp,"--------------------------\n");
            
            
            fprintf(fp,"\n\n-------------------------------------------------------\n");
			fclose(fp);			
		}
	}
	else{
		return;
	}

}
void printHelp(){
		printf("此程式以一隻股票基本面出發，透過資產負債表、損益表等等報表判斷公司體質。會有6個基本的財政比率\n");
		printf("1.流動比率:是一間公司的短期債務儕還能力跟短期風險的指標。(>2:良好，1~2:一般)\n");
		printf("2.負債率:一家公司所有資產中，有多少是由負債產生的。（此指標需與同行業做比較，尤其金融類股這類負債率較高的行業）\n");
		printf("3.銷貨報酬率:每銷售一元所賺取利潤的數量\n");
		printf("4.股東權益報酬率：投資的報酬率\n");
		printf("5.總收益成長:與過去3年做比較(良好:10%%~20%%)\n");
		printf("6.淨收益成長：總收益扣除成本含稅（良好:10%%~20%%)\n\n");
}

int main(){
	printf("\n這是一隻由陳品洋(Pin-Yang, Chen)所開發的程式，請問您會使用這支程式嗎？(y/n)\n");
	char yn,yn2;
	scanf("%c",&yn);
	int flag=0;
	if(yn=='y'||yn=='Y'){
		flag=1;
	}
	if(yn=='n'||yn=='N'){
		flag=1;
		printHelp();
	}
	if(flag==0){
		printf("請輸入y或n\n");
		return 0;
	}

	int flag2=1;	
	int idx=0;
	int CA[100],CD[100],OA[100],OD[100],R[100],R1[100],R2[100],R3[100],OR[100],OR1[100],OR2[100],OR3[100],StockRight[100];	
	float Rr1[100],Rr2[100],Rr3[100],Rr4[100],Rr5[100],Rr6[100];
	char Name[100][100];
	int Total[100];
	while(flag2==1){
		printf("\n\n-------------------------------------------------------\n");
		printf("請輸入第%d間公司名稱：",idx+1);
		scanf("%s",Name[idx]);
		printf("請輸入流動資產:");
		scanf("%d",&CA[idx]);
		printf("請輸入流動負債:");
		scanf("%d",&CD[idx]);
		printf("請輸入總資產:");
		scanf("%d",&OA[idx]);
		printf("請輸入總負債:");
		scanf("%d",&OD[idx]);
		printf("請輸入淨收入與過去三年淨收入：");
		scanf("%d%d%d%d",&R[idx],&R1[idx],&R2[idx],&R3[idx]);
		printf("請輸入總收入與過去三年總收入:");
		scanf("%d%d%d%d",&OR[idx],&OR1[idx],&OR2[idx],&OR3[idx]);
		printf("請輸入股東權益:");
		scanf("%d",&StockRight[idx]);

		
		Rr1[idx] = (float)CA[idx]/CD[idx]*100;
		Rr2[idx] = (float)OD[idx]/OA[idx]*100;
		Rr3[idx] = (float)R[idx]/OA[idx]*100;
		Rr4[idx] = (float)R[idx]/StockRight[idx]*100;
		Rr5[idx] = (float)OR[idx]/((OR1[idx]+OR2[idx]+OR3[idx])/3)*100;
		Rr6[idx] = (float)R[idx]/((R1[idx]+R2[idx]+R3[idx])/3)*100;
		Total[idx] = Rr1[idx]-Rr2[idx]+Rr3[idx]+Rr4[idx]+((Rr5[idx]+Rr6[idx])/2);

		printf("\n\n*********************************\n");
		printf("公司名稱:%s\n",Name[idx]);
		printf("流動比率：%.2f %%\n",Rr1[idx]);
		printf("負債率：%.2f %%\n",Rr2[idx]);
		printf("銷貨報酬率：%.2f %%\n",Rr3[idx]);
		printf("股東權益報酬率:%.2f %%\n",Rr4[idx]);
		printf("總收益成長：%.2f %%\n",Rr5[idx]);
		printf("淨收益成長：%.2f %%\n",Rr6[idx]);
		printf("粗估總分：%d\n",Total[idx]);
		idx++;
		if(idx==1){
			printf("\n\n-------------------------------------------------------\n");
			printf("請問是否與同行比較?(y/n)\n");
		}
		else{
			printf("\n\n-------------------------------------------------------\n");
			printf("請問是否繼續比較？(y/n)\n");

		}
		
		scanf("%s",&yn2);
		if(yn2=='y'||yn2=='Y'){
			flag2=1;
		}
		else if(yn2=='n'||yn2=='N'){
			flag2=0;
			if(idx>1){
				printf("\n\n-------------------------------------------------------\n");
				printf("比較排序:\n");

				printf("--------------------------\n");
				bubble(Name,Total,idx);
				printf("|%7s  %15s|\n","Co.","TotalRank");
				printf("**************************\n");
				for(int i=0;i<idx;i++){
					printf("|%7s  %15d|\n",Name[i],Total[i]);
				}
				printf("--------------------------\n");
				bubble(Name,(int *)Rr1,idx);
				printf("|%7s  %15s|\n","Co.","CurrentRatio");
				printf("**************************\n");
				for(int i=0;i<idx;i++){
					printf("|%7s  %15.2f|\n",Name[i],Rr1[i]);
				}
				printf("--------------------------\n");
				bubble(Name,(int *)Rr2,idx);
				printf("|%7s  %15s|\n","Co.","DebtRatio");
				printf("**************************\n");
				for(int i=0;i<idx;i++){
					printf("|%7s  %15.2f|\n",Name[i],Rr2[i]);
				}
				printf("--------------------------\n");
				bubble(Name,(int *)Rr3,idx);
				printf("|%7s  %15s|\n","Co.","ReturnOnSales");
				printf("**************************\n");
				for(int i=0;i<idx;i++){
					printf("|%7s  %15.2f|\n",Name[i],Rr3[i]);
				}
				printf("--------------------------\n");
				bubble(Name,(int *)Rr4,idx);
				printf("|%7s  %15s|\n","Co.","ReturnOnEquity");
				printf("**************************\n");
				for(int i=0;i<idx;i++){
					printf("|%7s  %15.2f|\n",Name[i],Rr4[i]);
				}
				printf("--------------------------\n");
				bubble(Name,(int *)Rr5,idx);
				printf("|%7s  %15s|\n","Co.","RevenueGrowth");
				printf("**************************\n");
				for(int i=0;i<idx;i++){
					printf("|%7s  %15.2f|\n",Name[i],Rr5[i]);
				}
				printf("--------------------------\n");
				bubble(Name,(int *)Rr6,idx);
				printf("|%7s  %15s|\n","Co.","NetIncome");
				printf("**************************\n");
				for(int i=0;i<idx;i++){
					printf("|%7s  %15.2f|\n",Name[i],Rr6[i]);
				}
				printf("--------------------------\n");

				
				printf("\n\n-------------------------------------------------------\n");
				printf("是否儲存結果?(y/n)\n");
				char yn3;
				scanf("%s",&yn3);
				fileSafe(Name,yn3,Total,Rr1,Rr2,Rr3,Rr4,Rr5,Rr6,idx);
			}
			
		}


		else{
			printf("錯誤！\n");
			return 0;
		}
	}
	printf("\n...輸入任意鍵結束...\n");
	int num;
	scanf("%d",&num);
	if(num){
		return 0;
	}
	
	return 0;
}
