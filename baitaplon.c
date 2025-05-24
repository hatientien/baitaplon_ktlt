#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
typedef struct tangCa{
char ngayTangCa[12];
char caTang[10];
char batDau[7];
char ketThuc[7];
struct tangCa *next;
}tangCa;
typedef struct lichNghi{
char ngayNghi[12];
char caNghi[10];
char batDau[7];
char ketThuc[7];
struct lichNghi *next;
}lichNghi;
typedef struct LichLam{
char caLam[10];
char batDau[7];
char ketThuc[7];
struct LichLam *next;
}LichLam;
typedef struct NhanVien{
    char hoTen[50];
    char ngayLam[12];
    char gioiTinh[5];
    char ngaySinh[12];
    float luong;
    char maNV[11];
    LichLam *LichLam;
    tangCa *tangCa;
    lichNghi *lichNghi;
}NhanVien;
//ham cap phat bo nho cho bien nhan vien
NhanVien *capPhat(int n, NhanVien *nv){
    NhanVien *newNV=(NhanVien*)realloc(nv, n*sizeof(NhanVien));
    if(newNV==NULL){
        printf("Khong the cap phat bo nho !");
        return NULL;
    }
    return newNV;
}
//ham them nhan vien vao danh sach
void themNhanVien(NhanVien **nv,int n, int m){
    *nv=capPhat(n+m,*nv);
    for(int i=m;i<n+m;i++){
        printf("Nhap ho ten: ");
        fgets((*nv)[i].hoTen,sizeof((*nv)[i].hoTen),stdin);
        (*nv)[i].hoTen[strcspn((*nv)[i].hoTen,"\n")]='\0';
         printf("Gioi tinh: ");
        fgets((*nv)[i].gioiTinh,sizeof((*nv)[i].gioiTinh),stdin);
        (*nv)[i].gioiTinh[strcspn((*nv)[i].gioiTinh,"\n")]='\0';
        printf("Nhap ngay sinh (vd: 09/11/2006): ");
        fgets((*nv)[i].ngaySinh,sizeof((*nv)[i].ngaySinh),stdin);
        (*nv)[i].ngaySinh[strcspn((*nv)[i].ngaySinh,"\n")]='\0';
         printf("Nhap ngay lam (vd: 09/11/2006): ");
        fgets((*nv)[i].ngayLam,sizeof((*nv)[i].ngayLam),stdin);
        (*nv)[i].ngayLam[strcspn((*nv)[i].ngayLam,"\n")]='\0';
         printf("Nhap ma nhan vien: ");
        fgets((*nv)[i].maNV,sizeof((*nv)[i].maNV),stdin);
        (*nv)[i].maNV[strcspn((*nv)[i].maNV,"\n")]='\0';
        printf("Luong: ");
        scanf("%f",&(*nv)[i].luong);
        getchar();
        (*nv)[i].LichLam=NULL;
        (*nv)[i].tangCa=NULL;
        (*nv)[i].lichNghi=NULL;
    }
}
//ham cap nhat thong tin sinh vien
void capNhatThongTinNhanVien(NhanVien *nv, int m){
        if(nv==NULL){
                printf("Danh sach rong !");
                return;
        }
        char maNv[12];
        printf("Nhap ma nhan vien cua nhan vien ban muon thay doi thong tin: ");
        fgets(maNv,sizeof(maNv),stdin);
        maNv[strcspn(maNv,"\n")]='\0';
        for(int i=0;i<m;i++){
                 if(strcmp(maNv,nv[i].maNV)==0){
                        printf("Da tim thay nhan vien ban muon thay doi thong tin !\n");
                        printf("Nhap thong tin moi:\n");
                        printf("Nhap ho ten: ");
                        fgets(nv[i].hoTen,sizeof(nv[i].hoTen),stdin);
                        nv[i].hoTen[strcspn(nv[i].hoTen,"\n")]='\0';
                        printf("Gioi tinh: ");
                        fgets(nv[i].gioiTinh,sizeof(nv[i].gioiTinh),stdin);
                        nv[i].gioiTinh[strcspn(nv[i].gioiTinh,"\n")]='\0';
                        printf("Nhap ngay sinh (vd: 09/11/2006): ");
                        fgets(nv[i].ngaySinh,sizeof(nv[i].ngaySinh),stdin);
                        nv[i].ngaySinh[strcspn(nv[i].ngaySinh,"\n")]='\0';
                        printf("Nhap ngay lam (vd: 09/11/2006): ");
                        fgets(nv[i].ngayLam,sizeof(nv[i].ngayLam),stdin);
                       nv[i].ngayLam[strcspn(nv[i].ngayLam,"\n")]='\0';
                        printf("Nhap ma nhan vien: ");
                        fgets(nv[i].maNV,sizeof(nv[i].maNV),stdin);
                        nv[i].maNV[strcspn(nv[i].maNV,"\n")]='\0';
                        printf("Luong: ");
                        scanf("%f",&nv[i].luong);
                        getchar();
                        printf("Da cap nhat thanh cong !\n");
                        return ;
                        }
                }
        printf("Khong tim thay nhan vien co ma: %s\n",maNv);
}
//ham xoa nhan vien khoi danh sach
void xoaNhanVien(NhanVien *nv,int *m){
         if(nv==NULL){
                printf("Danh sach rong !");
                return;
        }
        char maNv[12];
        printf("Nhap ma nhan vien cua nhan vien ban muon xoa: ");
        fgets(maNv,sizeof(maNv),stdin);
        maNv[strcspn(maNv,"\n")]='\0';
        for(int i=0;i<*m;i++){
                 if(strcmp(maNv,nv[i].maNV)==0){
                        LichLam *ll =nv[i].LichLam;
                       while (ll!= NULL) {
                                LichLam *llTemp = ll;
                                ll = ll->next;
                                free(llTemp);
                        }
                        tangCa *tc = nv[i].tangCa;
                        while (tc != NULL) {
                                tangCa *tcTemp = tc;
                                tc = tc->next;
                                free(tcTemp);
                                }
                        lichNghi *ln = nv[i].lichNghi;
                        while (ln != NULL) {
                                lichNghi *lnTemp = ln;
                                ln = ln->next;
                                free(lnTemp);
                                }
                        for(int j=i;j<*m-1;j++){
                                nv[j]=nv[j+1];
                        }
                        (*m)--;
                        printf("Da xoa nhan vien co ma so %s\n",maNv);
                        return;
                }
        }
        printf("Khong tim thay nhan vien ma ban muon\n");
}
//ham nhap lich lam co dinh cho cac nhan vien trong danh sach
void nhapLichLam(NhanVien *nv, int m){
        if(nv==NULL){
                printf("Danh sach rong !\n");
        }
        for(int i=0;i<m;i++){
                printf("Nhap lich lam cho nhan vien: %s\n",nv[i].hoTen);
                LichLam *newLichLam=(LichLam*)malloc(sizeof(LichLam));
                if(newLichLam==NULL){
                        printf("Khong the nhap lich !");
                        continue;
                }
                newLichLam->next=NULL;
                printf("Nhap thong tin ca lam (co dinh):\n");
                printf("Ca lam (sang-chieu-toi): ");
                fgets(newLichLam->caLam,sizeof(newLichLam->caLam),stdin);
                newLichLam->caLam[strcspn(newLichLam->caLam,"\n")]='\0';
                printf("Gio bat dau ca (00:00): ");
                fgets(newLichLam->batDau,sizeof(newLichLam->batDau),stdin);
                newLichLam->batDau[strcspn(newLichLam->batDau,"\n")]='\0';
                printf("Gio ket thuc ca (00:00): ");
                fgets(newLichLam->ketThuc,sizeof(newLichLam->ketThuc),stdin);
                newLichLam->ketThuc[strcspn(newLichLam->ketThuc,"\n")]='\0';
                if(nv[i].LichLam==NULL){
                nv[i].LichLam=newLichLam;
                }
                else{
                        LichLam *temp =nv[i].LichLam;
                        while(temp->next!=NULL){
                                temp=temp->next;
                        }
                        temp->next=newLichLam;
                }
        }
}
//ham them ca lam co dinh cho tung nhan vien
void themCaLamTungNhanVien(NhanVien *nv, int m){
        if(nv==NULL){
                printf("Danh sach rong !\n");
                return;
        }
        char hoten[50];
        printf("Nhap ten nhan vien: ");
        fgets(hoten,sizeof(hoten),stdin);
        hoten[strcspn(hoten,"\n")]='\0';
        int test=0;
        for(int i=0;i<m;i++){
                if(strcasecmp(nv[i].hoTen,hoten)==0){
                        printf("Da tim thay nhan vien muon cap nhat.\n");
                        LichLam *ll=(LichLam*)malloc(sizeof(LichLam));
                        if(ll==NULL){
                                printf("Khong the cap phat !\n");
                                return;
                        }
                        ll->next=NULL;
                        printf("Nhap thong tin ca lam : \n");
                        printf("Ca lam (sang-chieu-toi): ");
                        fgets(ll->caLam,sizeof(ll->caLam),stdin);
                        ll->caLam[strcspn(ll->caLam,"\n")]='\0';
                       printf("Gio bat dau ca (00:00): ");
                        fgets(ll->batDau,sizeof(ll->batDau),stdin);
                        ll->batDau[strcspn(ll->batDau,"\n")]='\0';
                        printf("Gio ket thuc ca (00:00): ");
                        fgets(ll->ketThuc,sizeof(ll->ketThuc),stdin);
                        ll->ketThuc[strcspn(ll->ketThuc,"\n")]='\0';
                        LichLam *temp = nv[i].LichLam;
                        if (temp == NULL) {
                        nv[i].LichLam = ll;
                        } else {
                        while (temp->next != NULL) {
                        temp = temp->next;
                        }
                        temp->next = ll;
                        }
                        printf("Cap nhat thanh cong.\n");
                        test=1;
                        return;
                }
        }
        if(!test){
        printf("Khong tim thay !\n");
        }
}
//ham nhap lich tang ca cho nhan vien
void nhapLichTangCa(NhanVien *nv,int m){
        if(nv==NULL){
                printf("Danh sach rong !\n");
                return;
        }
        char hoten[50];
        printf("Nhap ten nhan vien dang ki tang ca: ");
        fgets(hoten,sizeof(hoten),stdin);
        hoten[strcspn(hoten,"\n")]='\0';
        int test=0;
        for(int i=0;i<m;i++){
                if(strcasecmp(hoten,nv[i].hoTen)==0){
                                if(nv[i].LichLam==NULL){
                                        printf("Hay nhap lich lam co dinh truoc khi tang ca. \n");
                                        return;
                                }
                        printf("Da tim thay nhan vien: %s\n",nv[i].hoTen);
                        tangCa *tc=(tangCa*)malloc(sizeof(tangCa));
                        if(tc==NULL){
                                printf("Khong the cap phat bo nho !\n");
                                return;
                        }
                        tc->next=NULL;
                        printf("Nhap ngay tang ca (vd: 09/11/2006): ");
                       fgets(tc->ngayTangCa,sizeof(tc->ngayTangCa),stdin);
                       tc->ngayTangCa[strcspn(tc->ngayTangCa,"\n")]='\0';
                       printf("Nhap thoi gian tang ca:\n");
                       printf("Ca lam tang ca (sang-chieu-toi): ");
                       fgets(tc->caTang,sizeof(tc->caTang),stdin);
                       tc->caTang[strcspn(tc->caTang,"\n")]='\0';
                       printf("Gio bat dau ca (00:00): ");
                        fgets(tc->batDau,sizeof(tc->batDau),stdin);
                        tc->batDau[strcspn(tc->batDau,"\n")]='\0';
                        printf("Gio ket thuc ca (00:00): ");
                        fgets(tc->ketThuc,sizeof(tc->ketThuc),stdin);
                        tc->ketThuc[strcspn(tc->ketThuc,"\n")]='\0';
                        if(nv[i].tangCa==NULL){
                                nv[i].tangCa=tc;
                        }
                        else{
                                tangCa *temp=nv[i].tangCa;
                                while(temp->next!=NULL){
                                        temp=temp->next;
                                }
                                temp->next=tc;
                        }
                        printf("Da dang ki tang ca thanh cong !\n");
                        test=1;
                       return;
                }
        }
        if(!test){
                printf("Khong tim thay !");
        }
}
//ham nhap lich xin nghi cho nhan vien
void nhapLichNghi(NhanVien *nv,int m){
         if(nv==NULL){
                printf("Danh sach rong !\n");
                return;
        }
        char hoten[50];
        printf("Nhap ten nhan vien dang ki nghi: ");
        fgets(hoten,sizeof(hoten),stdin);
        hoten[strcspn(hoten,"\n")]='\0';
        int test=0;
        for(int i=0;i<m;i++){
                if(strcasecmp(hoten,nv[i].hoTen)==0){
                        if(nv[i].LichLam==NULL){
                                printf("Hay nhap lich lich lam co dinh truoc khi nghi.\n");
                                return;
                        }
                        printf("Da tim thay nhan vien: %s\n",nv[i].hoTen);
                        lichNghi *ln=(lichNghi*)malloc(sizeof(lichNghi));
                        if(ln==NULL){
                                printf("Khong the cap phat bo nho !\n");
                                return;
                        }
                        ln->next=NULL;
                        printf("Nhap ngay nghi (vd: 09/11/2006): ");
                       fgets(ln->ngayNghi,sizeof(ln->ngayNghi),stdin);
                       ln->ngayNghi[strcspn(ln->ngayNghi,"\n")]='\0';
                       printf("Nhap thoi gian:\n");
                       printf("Nhap ca nghi (sang-chieu-toi): ");
                       fgets(ln->caNghi,sizeof(ln->caNghi),stdin);
                       printf("Gio bat dau nghi (00:00): ");
                        fgets(ln->batDau,sizeof(ln->batDau),stdin);
                        ln->batDau[strcspn(ln->batDau,"\n")]='\0';
                        printf("Gio ket thuc nghi (00:00): ");
                        fgets(ln->ketThuc,sizeof(ln->ketThuc),stdin);
                        ln->ketThuc[strcspn(ln->ketThuc,"\n")]='\0';
                        if(nv[i].lichNghi==NULL){
                                nv[i].lichNghi=ln;
                        }
                        else{
                                lichNghi *temp=nv[i].lichNghi;
                                while(temp->next!=NULL){
                                        temp=temp->next;
                                }
                                temp->next=ln;
                        }
                        printf("Da dang ki nghi thanh cong !\n");
                        test=1;
                        return;
                 }
        }
        if(!test){
                printf("Khong tim thay !");
        }
}
//ham cap nhat lich lam co dinh
void capNhatLichLam(NhanVien *nv, int m){
        if(nv==NULL){
                printf("Danh sach rong !\n");
                return;
        }
        char hoten[50];
        printf("Nhap  ho ten nhan vien ban muon thay doi lich lam: ");
        fgets(hoten,sizeof(hoten),stdin);
        hoten[strcspn(hoten,"\n")]='\0';
        int t =0;
        for(int i=0;i<m;i++){
                if(strcasecmp(hoten,nv[i].hoTen)==0){
                        printf("Da tim thay nhan vien: %s\n",nv[i].hoTen);
                        if(nv[i].LichLam==NULL){
                                printf("Nhan vien nay chua co lich lam !\n");
                                return;
                        }
                        int dem =1;
                        LichLam *ll=nv[i].LichLam;
                        printf("Lich lam hien co la:\n");
                        while(ll!=NULL){
                                printf("[%d]: ca %s - (%s - %s)\n",dem,ll->caLam,ll->batDau,ll->ketThuc);
                                dem++;
                                ll=ll->next;
                        }
                        int test;
                        ll=nv[i].LichLam;
                        LichLam *temp=NULL;
                        dem=1;
                        printf("Nhap so thu tu ca ma ban muon thay doi; ");
                        scanf("%d",&test);
                        getchar();
                        while(ll!=NULL&&dem<test){
                                temp=ll;
                                ll=ll->next;
                                dem++;
                        }
                        if(ll==NULL){
                                printf("Ca lam khong hop le !\n");
                                return;
                        }
                        int choice;
                        printf("1. Thay doi gio cua ca lam\n");
                        printf("2. Xoa ca lam\n");
                        printf("Lua chon cua ban la: ");
                        scanf("%d",&choice);
                        getchar();
                        if(choice ==1){
                                printf("Cap nhat thoi gian moi:\n");
                                 printf("Gio bat dau ca (00:00): ");
                                fgets(ll->batDau,sizeof(ll->batDau),stdin);
                                ll->batDau[strcspn(ll->batDau,"\n")]='\0';
                                printf("Gio ket thuc ca (00:00): ");
                                fgets(ll->ketThuc,sizeof(ll->ketThuc),stdin);
                                ll->ketThuc[strcspn(ll->ketThuc,"\n")]='\0';
                                printf("Da cap nhat lich thanh cong\n");
                                return;
                        }
                        else if(choice==2){
                                if (temp==NULL) {
                                nv[i].LichLam = ll->next;
                                } else {
                                temp->next = ll->next;
                                }
                                free(ll);
                                printf("Da xoa ca lam o vi tri %d.\n", test);
                                return;
                                }
                        else {
                printf("Lua chon khong hop le.\n");
            }
                t=1;
                }
        }
        if(!t){
                printf("Khong tim thay nhan vien !\n");
        }
}
//ham in danh sach thong tin nhan vien
void inDanhSachNhanVien(NhanVien *nv,int n){
    int stt=0;
    printf("\n========================================Danhsach======================================\n");
    printf("---------------------------------------------------------------------------------------\n");
    printf("|stt|Ho va ten             |Ma nhan vien|Gioi tinh|Ngay sinh  |Ngay lam   |Luong      |\n");
    for(int i=0;i<n;i++){
       printf("---------------------------------------------------------------------------------------\n");
       printf("|%-3d|%-22s|%-12s|%-9s|%-11s|%-11s|%6.3f/gio|\n",++stt,nv[i].hoTen,nv[i].maNV,nv[i].gioiTinh,nv[i].ngaySinh,nv[i].ngayLam,nv[i].luong);
    }
 printf("---------------------------------------------------------------------------------------\n");
}
//ham tach nam trong chuoi thoi gian
int tachNam(char *a){
    int x,y,z;
    sscanf(a,"%d/%d/%d",&x,&y,&z);
    return z;
}
//ham tach thang trong chuoi thoi gian
int tachThang(char *a){
    int x,y,z;
    sscanf(a,"%d/%d/%d",&x,&y,&z);
    return y;
}
//ham tach ngay trong chuoi thoi gian
int tachNgay(char *a){
    int x,y,z;
    sscanf(a,"%d/%d/%d",&x,&y,&z);
    return x;
}
//ham sap xep nhan vien theo do tuoi
void sapxeptheoDoTuoi(NhanVien *nv, int m){
    for(int i=0;i<m-1;i++){
       for(int j=i+1;j<m;j++){
           if(tachNam(nv[i].ngaySinh)>=tachNam(nv[j].ngaySinh)){
               NhanVien temp=*(nv+i);
               *(nv+i)=*(nv+j);
               *(nv+j)=temp;
           }
       }
    }
}
//ham tim ra ca nhan vien da va toi han nghi huu
void timNhanVienSapNghiHuu(NhanVien *nv,int m){
if(nv==NULL){
        printf("Danh sach rong !");
        return;
}
        int nam;
        printf("nhap nam ban muon chon: ");
        scanf("%d",&nam);
                getchar();
        printf("Cac nhan vien duoc nghi huu vao nam %d la: \n",nam);
        for(int i=0;i<m;i++){
                int namSinh=tachNam(nv[i].ngaySinh);
                if(nam-namSinh>=60){
                printf("%s\n",nv[i].hoTen);
                }
        }
}
//ham tach danh sach theo gioi tinh
void tachDanhSach(NhanVien *nv ,NhanVien **NvNam, NhanVien **NvNu, int m, int *dem1,int *dem2){
        if(nv==NULL){
                printf("Danh sach rong !\n");
                return;
        }
        *dem1=0;
        *dem2=0;
        for(int i=0;i<m;i++){
              if(strcasecmp(nv[i].gioiTinh,"nam")==0){
                (*NvNam)=capPhat(*dem1+1,*NvNam);
                if (*NvNam == NULL) return;
                (*NvNam)[*dem1]=nv[i];
                (*dem1)++;
              }
              else{
                *NvNu=capPhat(*dem2+1,*NvNu);
                if (*NvNu == NULL) return;
               (*NvNu)[*dem2]=nv[i];
                (*dem2)++;
              }
        }
}
//tinh khoang cach thoi gian
float KhoangCachThoiGian(char *a, char *b) {
    int x1, x2, y1, y2;
    sscanf(a, "%d:%d",&x1,&x2);
    sscanf(b, "%d:%d",&y1,&y2);
    int start=x1*60+x2;
    int end = y1*60+y2;

    if (end<start) {
        end+=24*60;
    }
    return (float)(end-start)/60;
}
//ham tinh tong gio lam thuc te hang thang
float tinhGioLam(NhanVien nv,int thang,int nam){
float tongGio=0;
LichLam *ll=nv.LichLam;
if(tachNam(nv.ngayLam)>nam)
        return 0;
else if(tachThang(nv.ngayLam)>thang&&tachNam(nv.ngayLam)==nam)
        return 0;
if(ll==NULL){
        printf("Nhan vien chua co lich lam !\n");
        return 0;
}
        while(ll!=NULL){
       tongGio+=26*KhoangCachThoiGian(ll->batDau,ll->ketThuc);
       ll=ll->next;
}
     tangCa *tc=nv.tangCa;
                while(tc!=NULL){
                        if(tachThang(tc->ngayTangCa)==thang&&tachNam(tc->ngayTangCa)==nam){
                                tongGio+=KhoangCachThoiGian(tc->batDau,tc->ketThuc);
                }
                  tc=tc->next;
        }
        lichNghi *ln=nv.lichNghi;
                while(ln!=NULL){
                        if(tachThang(ln->ngayNghi)==thang&&tachNam(ln->ngayNghi)==nam){
                                tongGio-=KhoangCachThoiGian(ln->batDau,ln->ketThuc);
                }
                 ln=ln->next;
        }
return tongGio;
}
//ham tinh tong gio lam co dinh hang thang
float tinhGioLamCoDinh(NhanVien nv) {
        if(nv.LichLam==NULL){
                return 0;
        }
    float tongGio = 0;
    LichLam *ll = nv.LichLam;
    while (ll != NULL) {
        tongGio += 26 * KhoangCachThoiGian(ll->batDau, ll->ketThuc);
        ll = ll->next;
    }
    return tongGio;
}
//ham tinh tong luong cua moi nhan vien
float tongLuong(NhanVien nv,int thang,int nam){
float tongluong=nv.luong*tinhGioLam(nv,thang,nam);
return tongluong;
}
//ham in ra danh sach ca lam cho tat ca nhan vien
void InDanhSachCaLam(NhanVien *nv, int m) {
    if (nv == NULL) {
        printf("Danh sach rong !\n");
        return;
    }
    for (int i = 0; i < m; i++) {
        printf("Ca lam cua nhan vien %s la:\n", nv[i].hoTen);
        if (nv[i].LichLam == NULL) {
            printf("Nhan vien nay chua co lich lam !\n");
            printf("-------------------------------------------------\n");
            continue;
        }
        int dem = 1;
        LichLam *ll = nv[i].LichLam;
        printf("Lich lam co dinh la:\n");
        while (ll != NULL) {
            printf("[%d]. Ca %s - (%s - %s)\n", dem, ll->caLam, ll->batDau, ll->ketThuc);
            ll = ll->next;
            dem++;
        }
        dem = 1;
        printf("Lich tang ca:\n");
        if (nv[i].tangCa == NULL) {
            printf("Khong co lich tang ca !\n");
        } else {
            tangCa *tc = nv[i].tangCa;
            while (tc != NULL) {
                printf("[%d]. Ngay %s - Ca %s - (%s - %s)\n", dem, tc->ngayTangCa, tc->caTang, tc->batDau, tc->ketThuc);
                tc = tc->next;
                dem++;
            }
        }
        dem = 1;
        printf("Lich nghi:\n");
        if (nv[i].lichNghi == NULL) {
            printf("Khong co lich nghi !\n");
        } else {
            lichNghi *ln = nv[i].lichNghi;
            while (ln != NULL) {
                printf("[%d]. Ngay %s - Ca %s - (%s - %s)\n", dem, ln->ngayNghi, ln->caNghi, ln->batDau, ln->ketThuc);
                ln = ln->next;
                dem++;
            }
        }
        printf("-------------------------------------------------\n");
    }
}
//ham in danh sach thong ke hang thang
void inThongKeNhanVien(NhanVien *ds, int soLuong, int thang, int nam) {
    if (ds==NULL) {
        printf("Danh sach rong !\n");
        return;
    }
    printf("===== DANH SACH THONG KE NHAN VIEN THANG %d =====\n", thang);
    printf("%-5s %-20s %-15s %-25s %-25s %-25s %-15s\n","STT", "Ho Ten", "Ma NV", "Lich Lam Co Dinh","Tang Ca (ngay, gio)", "Nghi (ngay, gio)", "Tong Luong");
    for (int i = 0; i < soLuong; i++) {
        NhanVien nv = ds[i];
        printf("%-5d %-20s %-15s ", i+1,nv.hoTen,nv.maNV);
        LichLam *ll=nv.LichLam;
        if (ll==NULL){
            printf("%-25s ","Chua co");
        }
        else{
            LichLam *templl=ll;
            printf("[");
            while (templl!=NULL){
                printf("%s(%s-%s)",templl->caLam, templl->batDau, templl->ketThuc);
                if (templl->next != NULL) printf(", ");
                        templl = templl->next;
            }
            printf("]%-5s", "");
        }
        tangCa *tc=nv.tangCa;
        if (tc==NULL) {
            printf("%-25s ", "Khong co");
        }
        else{
                tangCa *tempTc = tc;
                printf("[");
                int in = 0;
                while (tempTc != NULL) {
                        if (tachThang(tempTc->ngayTangCa) == thang&&tachNam(tempTc->ngayTangCa)==nam) {
                        float gioTC = KhoangCachThoiGian(tempTc->batDau, tempTc->ketThuc);
                        printf("%s(%.1f gio)", tempTc->ngayTangCa, gioTC);
                        if (tempTc->next != NULL && tempTc->next->ngayTangCa[0] != '\0') printf(", ");
                        in = 1;
                        }
                        tempTc = tempTc->next;
                }
                if (!in) printf("Khong co");
                printf("]%-3s", "");
                }
        lichNghi *ln = nv.lichNghi;
        if (ln==NULL) {
                printf("%-25s ","Khong co");
        }
        else{
                lichNghi *templn = ln;
                printf("[");
                int test=0;
                while (templn!=NULL) {
                        if (tachThang(templn->ngayNghi)==thang){
                                float gioNghi = KhoangCachThoiGian(templn->batDau, templn->ketThuc);
                                printf("%s(%.1f gio)", templn->ngayNghi, gioNghi);
                                if (templn->next!=NULL && templn->next->ngayNghi[0] != '\0')
                                        printf(", ");
                                test=1;
                        }
                templn=templn->next;
            }
            if (!test)
                printf("Khong co");
                printf("]%-3s", "");
                }
        float luong=tongLuong(nv, thang,nam);
        printf("%-15.2ftrieu\n",luong);
    }
}
//ham in ra ca lam ma nhan vien ban muon
void timCaLamNhanVien(NhanVien *nv, int m){
        if(nv==NULL){
                printf("Danh sach rong !\n");
                return;
        }
        char maNv[12];
          printf("Nhap ma nhan vien cua nhan vien ban muon tim: ");
        fgets(maNv,sizeof(maNv),stdin);
        maNv[strcspn(maNv,"\n")]='\0';
        for(int i=0;i<m;i++){
              if(strcmp(nv[i].maNV,maNv)==0){
                        if(nv[i].LichLam==NULL){
                                printf("Nhan vien chua co lich lam !\n");
                                return;
                        }
                int dem=1;
                 LichLam *ll=nv[i].LichLam;
                 printf("Lich lam co dinh cua nhan vien %s la:\n",nv[i].hoTen);
                        while(ll!=NULL){
                                printf("[%d]. Ca %s - (%s - %s)\n",dem,ll->caLam,ll->batDau,ll->ketThuc);
                                ll=ll->next;
                                dem++;
                                }
                                dem=1;
                                tangCa *tc=nv[i].tangCa;
                                printf("Lich tang ca:\n");
                        if(tc==NULL){
                                printf("Khong co lich tang ca !");
                                }
                        else{
                                while(tc!=NULL){
                                        printf("[%d]. Ngay %s - Ca %s - (%s - %s)\n",dem,tc->ngayTangCa,tc->caTang,tc->batDau,tc->ketThuc);
                                        tc=tc->next;
                                        dem++;
                                }
                        }
                        dem=1;
                        lichNghi *ln=nv[i].lichNghi;
                        printf("Lich nghi:\n");
                        if(ln==NULL){
                                printf("Khong co lich nghi !");
                        }
                        else{
                                while(ln!=NULL){
                                        printf("[%d]. Ngay %s - Ca %s - (%s - %s)\n",dem,ln->ngayNghi,ln->caNghi,ln->batDau,ln->ketThuc);
                                        ln=ln->next;
                                        dem++;
                                }
                        }
                }
        }
}
void freedsGioiTinh(NhanVien **nvNam, NhanVien **nvNu) {
    if (*nvNam != NULL) {
        free(*nvNam);
        *nvNam = NULL;
    }
    if (*nvNu != NULL) {
        free(*nvNu);
        *nvNu = NULL;
    }
}
// Ghi thong tin tat ca nhan vien ra file van ban
void ghiThongTinTatCaNhanVien(NhanVien *Nv, int m, const char *filename) {
    if (Nv == NULL || m <= 0) {
        printf("Khong co nhan vien de ghi thong tin.\n");
        return;
    }
    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("Loi mo file");
        return;
    }
    fprintf(f, "===== DANH SACH TOAN BO NHAN VIEN =====\n\n");
    for (int i = 0; i < m; i++) {
        fprintf(f, "----- Nhan vien thu %d -----\n", i + 1);
        fprintf(f, "Ma NV    : %s\n", Nv[i].maNV);
        fprintf(f, "Ho va ten: %s\n", Nv[i].hoTen);
        fprintf(f, "Ngay sinh: %s\n", Nv[i].ngaySinh);
        fprintf(f, "Gioi tinh: %s\n", Nv[i].gioiTinh);
        fprintf(f, "Ngay lam : %s\n", Nv[i].ngayLam);
        fprintf(f, "Luong    : %.2f\n", Nv[i].luong);
        fprintf(f, "---------------------------\n\n");
    }
    fclose(f);
    printf("Da ghi thong tin tat ca %d nhan vien vao file %s\n", m, filename);
}
//Ghi lich lam tat ca nhan vien ra file van ban
void ghiLichLamNhanVien(NhanVien *nv,int m){
        if(nv==NULL){
                printf("Danh sach nhan vien rong !\n");
                return;
        }
        FILE *f=fopen("LichLam.txt","w");
        if(f==NULL){
                printf("Khong the mo file !\n");
                return;
        }
        for(int i=0;i<m;i++){
                fprintf(f,"Nhan vien: %s | Ma NV: %s\n", nv[i].hoTen, nv[i].maNV);
                if(nv[i].LichLam==NULL){
                        fprintf(f,"Nhan vien nay chua co lich lam !\n");
                        fprintf(f,"-------------------------------------------------\n");
                        continue;
                }
                int dem=1;
                 LichLam *ll=nv[i].LichLam;
                 fprintf(f,"Lich lam co dinh la:\n");
                while(ll!=NULL){
                      fprintf(f,"[%d]. Ca %s - (%s - %s)\n",dem,ll->caLam,ll->batDau,ll->ketThuc);
                      ll=ll->next;
                      dem++;
                }
                dem=1;
                tangCa *tc=nv[i].tangCa;
                fprintf(f,"Lich tang ca:\n");
                if(tc==NULL){
                        fprintf(f,"Khong co lich tang ca !");
                }
                else{
                        while(tc!=NULL){
                                fprintf(f,"[%d]. Ngay %s - Ca %s - (%s -%s)\n",dem,tc->ngayTangCa,tc->caTang,tc->batDau,tc->ketThuc);
                                tc=tc->next;
                                dem++;
                        }
                }
                dem=1;
                lichNghi *ln=nv[i].lichNghi;
                fprintf(f,"Lich nghi:\n");
                if(ln==NULL){
                       fprintf(f,"Khong co lich nghi !");
                }
                else{
                        while(ln!=NULL){
                                fprintf(f,"[%d]. Ngay %s - Ca %s - (%s -%s)\n",dem,ln->ngayNghi,ln->caNghi,ln->batDau,ln->ketThuc);
                                ln=ln->next;
                                dem++;
                        }
                }
                fprintf(f,"-------------------------------------------------\n");
        }
        fclose(f);
}
//ham giai phong bo nho cua con tro lich lam
void freeLichLam(NhanVien *nv, int m) {
    for (int i = 0; i < m; i++) {
        LichLam *ll = nv[i].LichLam;
        while (ll != NULL) {
            LichLam *llTemp = ll;
            ll = ll->next;
            free(llTemp);
        }
    }
}
void freeLichNghi(NhanVien *nv, int m) {
    if (nv == NULL) return;
    for (int i = 0; i < m; i++) {
        lichNghi *ln = nv[i].lichNghi;
        while (ln != NULL) {
            lichNghi *temp = ln;
            ln = ln->next;
            free(temp);
        }
        nv[i].lichNghi = NULL;
    }
}
void freeTangCa(NhanVien *nv, int m) {
    if (nv == NULL) return;
    for (int i = 0; i < m; i++) {
        tangCa *tc = nv[i].tangCa;
        while (tc != NULL) {
            tangCa *temp = tc;
            tc = tc->next;
            free(temp);
        }
        nv[i].tangCa = NULL;
    }
}
void MENU(){
        printf("\n=================================================================\n");
        printf("|                     MENU QUAN LY NHAN VIEN                    |\n");
        printf("=================================================================\n");
        printf("|---------------------------NHAN SU-----------------------------|\n");
        printf("| 1. Them nhan vien moi                                         |\n");
        printf("| 2. Cap nhat thong tin nhan vien theo Ma NV                    |\n");
        printf("| 3. Xoa nhan vien theo Ma NV                                   |\n");
        printf("| 4. Sap xep nhan vien theo tuoi                                |\n");
        printf("| 5. Tach danh sach theo gioi tinh                              |\n");
        printf("| 6. Tim nhan vien sap nghi huu                                 |\n");
        printf("| 7. Hien thi danh sach nhan vien                               |\n");
        printf("| 8. Thong ke gio lam va luong theo thang                       |\n");
        printf("| 9. Ghi thong tin tat ca nhan vien ra file                     |\n");
        printf("|---------------------------LICH LAM----------------------------|\n");
        printf("| 10. Nhap lich lam co dinh cho nhan vien                       |\n");
        printf("| 11. Them ca lam co dinh moi cho mot nhan vien                 |\n");
        printf("| 12. Cap nhat/Xoa lich lam co dinh cho nhan vien               |\n");
        printf("| 13. Dang ky lich tang ca cho nhan vien                        |\n");
        printf("| 14. Dang ky lich nghi cho nhan vien                           |\n");
        printf("| 15. In chi tiet lich lam tat ca nhan vien                     |\n");
        printf("| 16. In chi tiet lich lam mot nhan vien                        |\n");
        printf("| 17. Ghi file lich lam cua tat ca nhan vien                    |\n");
        printf("|---------------------------------------------------------------|\n");
        printf("=================================================================\n");
}
int main() {
    NhanVien *Nv = NULL;
    int m = 0;
    NhanVien *NvNam = NULL, *NvNu = NULL;
    int demNam = 0, demNu = 0;
    int choice;
    do {
        MENU();
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1: {
                int n;
                do {
                    printf("Nhap so luong NV muon them: ");
                    scanf("%d", &n);
                    getchar();
                } while (n <= 0);
                themNhanVien(&Nv, n, m);
                m += n;
                break;
            }
            case 2:
                capNhatThongTinNhanVien(Nv, m);
                break;
            case 3:
                xoaNhanVien(Nv, &m);
                if (m == 0) {
                free(Nv);
                Nv = NULL;
                 }
                break;
            case 4:
                sapxeptheoDoTuoi(Nv, m);
                inDanhSachNhanVien(Nv, m);
                break;
            case 5:
                freedsGioiTinh(&NvNam, &NvNu);
                demNam = demNu = 0;
                tachDanhSach(Nv, &NvNam, &NvNu, m, &demNam, &demNu);
                if (demNam)
                        inDanhSachNhanVien(NvNam, demNam);
                if (demNu)
                        inDanhSachNhanVien(NvNu, demNu);
                break;
            case 6:
                timNhanVienSapNghiHuu(Nv, m);
                break;
            case 7:
                inDanhSachNhanVien(Nv,m);
                break;
            case 8:
                    {
                int thang;
                do {
                    printf("Nhap thang (1-12): ");
                    scanf("%d", &thang);
                    getchar();
                } while (thang < 1 || thang > 12);
                int nam;
                printf("Nhap nam: ");
                    scanf("%d", &nam);
                    getchar();
                inThongKeNhanVien(Nv, m, thang,nam);
                break;
            }
            case 9:
                ghiThongTinTatCaNhanVien(Nv, m, "tatca_nv.txt");
                printf("Da ghi ra file tatca_nv.txt\n");
                break;
            case 10:
                nhapLichLam(Nv, m);
                break;
            case 11:
                themCaLamTungNhanVien(Nv, m);
                break;
            case 12:
                capNhatLichLam(Nv, m);
                break;
            case 13:
                nhapLichTangCa(Nv, m);
                break;
            case 14:
                nhapLichNghi(Nv, m);
                break;
            case 15:
                InDanhSachCaLam(Nv, m);
                break;
            case 16:
                timCaLamNhanVien(Nv, m);
                break;
            case 17:
                ghiLichLamNhanVien(Nv, m);
                printf("Da ghi lich lam vao file LichLam.txt\n");
            case 0:
                printf("Dang thoat chuong trinh...\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (choice != 0);
    if (Nv){
        freeLichNghi(Nv,m);
        freeTangCa(Nv,m);
        freeLichLam(Nv, m);
        free(Nv);
    }
        freedsGioiTinh(&NvNam, &NvNu);
    printf("Chuong trinh ket thuc.\n");
    return 0;
}
