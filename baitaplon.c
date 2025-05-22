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
typedef struct phongBan{
char tenPB[30];
NhanVien *dsNhanVien;
int slNhanVien;
struct phongBan *next;
}phongBan;
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
//ham xoa thong tin nhan vien trong phong ban
void xoaThongTinNhanVienPhongBan(phongBan **head, char *maNv) {
        if (*head==NULL) {
                printf("Danh sach phong ban rong !\n");
                return;
        }
        phongBan *temp = *head;
        int found = 0;
        while (temp != NULL) {
                if (temp->dsNhanVien == NULL || temp->slNhanVien == 0) {
                temp = temp->next;
                continue;
                }
                for (int i = 0; i < temp->slNhanVien; i++) {
                if (strcmp(temp->dsNhanVien[i].maNV, maNv) == 0) {
                        LichLam *ll = temp->dsNhanVien[i].LichLam;
                        while (ll != NULL) {
                                LichLam *llTemp = ll;
                                ll = ll->next;
                                free(llTemp);
                        }
                        tangCa *tc = temp->dsNhanVien[i].tangCa;
                        while (tc != NULL) {
                                tangCa *tcTemp = tc;
                                tc = tc->next;
                                free(tcTemp);
                        }
                        lichNghi *ln = temp->dsNhanVien[i].lichNghi;
                        while (ln != NULL) {
                                lichNghi *lnTemp = ln;
                                ln = ln->next;
                                free(lnTemp);
                        }
                        for (int j = i; j < temp->slNhanVien - 1; j++) {
                                temp->dsNhanVien[j] = temp->dsNhanVien[j + 1];
                        }
                        temp->slNhanVien--;
                        if (temp->slNhanVien == 0) {
                                free(temp->dsNhanVien);
                                temp->dsNhanVien = NULL;
                        }
                        else {
                        temp->dsNhanVien = realloc(temp->dsNhanVien, sizeof(NhanVien) * temp->slNhanVien);
                        if (temp->dsNhanVien == NULL) {
                                printf("Loi cap phat lai bo nho sau khi xoa!\n");
                                return;
                        }
                }
                printf("Da xoa nhan vien co ma so %s khoi phong %s.\n", maNv, temp->tenPB);
                found = 1;
                return;
            }
        }
        temp = temp->next;
    }
    if (!found)
        printf("Khong tim thay nhan vien ma ban muon xoa trong phong ban!\n");
}
//ham cap nhat thong tin sinh vien
void capNhatThongTinNhanVien(NhanVien *nv, int m,phongBan *head){
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
                        if(head==NULL){
                                printf("Danh sach phong ban rong nen chi cap nhan trong danh sach tong !\n");
                                return;
                        }
                        while(head!=NULL){
                                if(head->dsNhanVien==NULL||head->slNhanVien==0){
                                        head=head->next;
                                        continue;
                                }
                                for(int j=0;j<head->slNhanVien;j++){
                                        if(strcmp(head->dsNhanVien[j].maNV,maNv)==0){
                                                strcpy(head->dsNhanVien[j].hoTen,nv[i].hoTen);
                                                strcpy(head->dsNhanVien[j].gioiTinh,nv[i].gioiTinh);
                                                strcpy(head->dsNhanVien[j].ngaySinh,nv[i].ngaySinh);
                                                strcpy(head->dsNhanVien[j].ngayLam,nv[i].ngayLam);
                                                strcpy(head->dsNhanVien[j].maNV,nv[i].maNV);
                                                head->dsNhanVien[j].luong=nv[i].luong;
                                                printf("Da cap nhan thong tin.\n");
                                                return;
                                        }
                                }
                        }
                 }
        }
        printf("Khong tim thay nhan vien co ma: %s\n",maNv);
}
//ham xoa nhan vien khoi danh sach
void xoaNhanVien(NhanVien *nv,int *m,phongBan **head){
         if(nv==NULL){
                printf("Danh sach rong !");
                return;
        }
        char maNv[12];
        printf("Nhap ma nhan vien cua nhan vien ban muon xoa: ");
        fgets(maNv,sizeof(maNv),stdin);
        maNv[strcspn(maNv,"\n")]='\0';
        xoaThongTinNhanVienPhongBan(head,maNv);
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
                if(strcmpi(hoten,nv[i].hoTen)==0){
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
                if(strcmpi(hoten,nv[i].hoTen)==0){
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
LichLam* cloneLichLam(LichLam *goc) {
    if (!goc) return NULL;
    LichLam *dau = NULL, *cuoi = NULL;
    while (goc) {
        LichLam *moi = (LichLam*)malloc(sizeof(LichLam));
        strcpy(moi->caLam, goc->caLam);
        strcpy(moi->batDau, goc->batDau);
         strcpy(moi->ketThuc, goc->ketThuc);
        moi->next = NULL;
        if (!dau) {
            dau = cuoi = moi;
        } else {
            cuoi->next = moi;
            cuoi = moi;
        }
        goc = goc->next;
    }
    return dau;
}
tangCa *cloneTangCa(tangCa *goc) {
    if (!goc) return NULL;
    tangCa *dau = NULL, *cuoi = NULL;
    while (goc) {
        tangCa *moi = (tangCa *)malloc(sizeof(tangCa));
        strcpy(moi->ngayTangCa, goc->ngayTangCa);
        strcpy(moi->caTang, goc->caTang);
        strcpy(moi->batDau, goc->batDau);
        strcpy(moi->ketThuc, goc->ketThuc);
        moi->next = NULL;
        if (!dau) dau = cuoi = moi;
        else cuoi = cuoi->next = moi;
        goc = goc->next;
    }
    return dau;
}
lichNghi *cloneLichNghi(lichNghi *goc) {
    if (!goc) return NULL;
    lichNghi *dau = NULL, *cuoi = NULL;
    while (goc) {
        lichNghi *moi = (lichNghi *)malloc(sizeof(lichNghi));
        strcpy(moi->ngayNghi, goc->ngayNghi);
        strcpy(moi->caNghi, goc->caNghi);
        strcpy(moi->batDau, goc->batDau);
        strcpy(moi->ketThuc, goc->ketThuc);
        moi->next = NULL;
        if (!dau) dau = cuoi = moi;
        else cuoi = cuoi->next = moi;
        goc = goc->next;
    }
    return dau;
}
void capNhatThongTinNhanVienVaoPhongBan(NhanVien *dsTong, int soLuongTong, phongBan *dsPhong) {
    if (!dsTong || soLuongTong == 0 || !dsPhong) {
        printf("Danh sach tong hoac phong ban rong.\n");
        return;
    }
    for (int i = 0; i < soLuongTong; i++) {
        NhanVien *nv = &dsTong[i];
        int daCapNhat = 0;
        phongBan *pb = dsPhong;
        while (pb) {
            for (int j = 0; j < pb->slNhanVien; j++) {
                if (strcmp(pb->dsNhanVien[j].maNV, nv->maNV) == 0) {
                    strcpy(pb->dsNhanVien[j].hoTen, nv->hoTen);
                    strcpy(pb->dsNhanVien[j].gioiTinh, nv->gioiTinh);
                    strcpy(pb->dsNhanVien[j].ngaySinh, nv->ngaySinh);
                    strcpy(pb->dsNhanVien[j].ngayLam, nv->ngayLam);
                    pb->dsNhanVien[j].luong = nv->luong;
                    LichLam *ll = pb->dsNhanVien[j].LichLam;
                    while (ll) {
                        LichLam *temp = ll;
                        ll = ll->next;
                        free(temp);
                    }
                        pb->dsNhanVien[j].LichLam = cloneLichLam(nv->LichLam);
                        pb->dsNhanVien[j].tangCa = cloneTangCa(nv->tangCa);
                        pb->dsNhanVien[j].lichNghi = cloneLichNghi(nv->lichNghi);
                    daCapNhat = 1;
                    break;
                }
            }
            if (daCapNhat) break;
            pb = pb->next;
        }
        if (!daCapNhat) {
            printf("Nhan vien %s chua co trong phong ban => KHONG cap nhat.\n", nv->maNV);
        }
    }
    printf("Da cap nhat thong tin nhan vien (va LichLam) tu danh sach tong vao cac phong ban.\n");
}

//ham in danh sach thong tin nhan vien
void inDanhSachNhanVien(NhanVien *nv,int n){
    int stt=0;
    printf("\n========================================Danh sach======================================\n");
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
//ham tinh tong gio lam thang
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
//ham tinh tong gio lam co dinh
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
//ham cap phat bo nho cho phong ban
phongBan *capPhatPhong(){
        phongBan *newpb=(phongBan*)malloc(sizeof(phongBan));
        if(newpb==NULL){
                return NULL;
        }
        newpb->dsNhanVien=NULL;
        newpb->next=NULL;
        return newpb;
}
//ham them phong ban
void themPhongBan(phongBan **head){
phongBan *newPB=capPhatPhong();
        if(newPB==NULL){
                printf("Khong the cap phat !\n");
                return;
        }
        printf("Nhap ten phong ban: ");
        fgets(newPB->tenPB,sizeof(newPB->tenPB),stdin);
        newPB->tenPB[strcspn(newPB->tenPB,"\n")]='\0';
        newPB->slNhanVien=0;
        newPB->next=NULL;
        if(*head==NULL){
                *head=newPB;
        }
         else{
                phongBan *temp=*head;
                while(temp->next!=NULL){
                        temp=temp->next;
                }
                temp->next=newPB;
         }
         printf("Them thanh cong !\n");
}
//ham thu xem nhan vien da co trong phong ban chua
int nhanVienDaCoTrongPhongBan(phongBan *head, char *maNV) {
    while (head != NULL) {
        for (int i = 0; i < head->slNhanVien; i++) {
            if (strcasecmp(head->dsNhanVien[i].maNV, maNV) == 0) {
                return 1;
            }
        }
        head = head->next;
    }
    return 0;
}
//ham them nhan vien vao phong ban
void themNhanVienVaoPhongBan(phongBan **head, NhanVien *nv, int m) {
    if (*head == NULL) {
        printf("Chua co phong ban nao !\n");
        return;
    }
    char tenPb[30];
    printf("Nhap ten phong ban ma ban muon them nhan vien: ");
    fgets(tenPb, sizeof(tenPb), stdin);
    tenPb[strcspn(tenPb, "\n")] = '\0';
    phongBan *pb = *head;
    while (pb != NULL && strcmp(tenPb, pb->tenPB) != 0) {
        pb = pb->next;
    }
    if (pb == NULL) {
        printf("Khong tim thay phong ban !\n");
        return;
    }
    int sl;
    printf("Nhap so luong nhan vien muon them vao: ");
    scanf("%d", &sl);
    getchar();
    for (int j = 0; j < sl; j++) {
        char hoten[50];
        printf("Nhap ho ten nhan vien muon them vao: ");
        fgets(hoten, sizeof(hoten), stdin);
        hoten[strcspn(hoten, "\n")] = '\0';
        int timThay = 0;
        int viTri = -1;
        for (int i = 0; i < m; i++) {
            if (strcmp(hoten, nv[i].hoTen) == 0) {
                viTri = i;
                timThay = 1;
                break;
            }
        }
        if (!timThay) {
            printf("Nhan vien nay khong ton tai trong danh sach nhan vien!\n");
            continue;
        }
        if (nhanVienDaCoTrongPhongBan(*head, nv[viTri].maNV)) {
            printf("Nhan vien '%s' da nam trong mot phong ban khac!\n", hoten);
            continue;
        }
        pb->dsNhanVien = realloc(pb->dsNhanVien, sizeof(NhanVien) * (pb->slNhanVien + 1));
        if (pb->dsNhanVien == NULL) {
            printf("Khong du bo nho de them nhan vien!\n");
            return;
        }
       pb->dsNhanVien[pb->slNhanVien] = nv[viTri]; // copy cơ bản
        pb->dsNhanVien[pb->slNhanVien].LichLam = cloneLichLam(nv[viTri].LichLam);
        pb->dsNhanVien[pb->slNhanVien].tangCa = cloneTangCa(nv[viTri].tangCa);
        pb->dsNhanVien[pb->slNhanVien].lichNghi = cloneLichNghi(nv[viTri].lichNghi);
        pb->slNhanVien++;
        printf("Them nhan vien '%s' vao phong ban '%s' thanh cong!\n", hoten, pb->tenPB);
    }
}
//ham in danh sach sinh vien trong phong ban
void inDanhSachNhanVienCuaPhong(phongBan *head){
        if(head == NULL){
                printf("Danh sach phong ban rong !\n");
                return;
        }
        while(head!=NULL){
                if(head->slNhanVien==0||head->dsNhanVien==NULL){
                        head=head->next;
                        continue;
                }
                int stt=0;
                printf("\n====================DANH SACH NHAN VIEN CUA PHONG %s===================\n",head->tenPB);
                printf("---------------------------------------------------------------------------------------\n");
                printf("|stt|Ho va ten             |Ma nhan vien|Gioi tinh|Ngay sinh  |Ngay lam   |Luong      |\n");
                for(int i=0;i<head->slNhanVien;i++){
                printf("---------------------------------------------------------------------------------------\n");
                printf("|%-3d|%-22s|%-12s|%-9s|%-11s|%-11s|%6.3f/gio|\n",++stt,head->dsNhanVien[i].hoTen,head->dsNhanVien[i].maNV,head->dsNhanVien[i].gioiTinh,head->dsNhanVien[i].ngaySinh,head->dsNhanVien[i].ngayLam,head->dsNhanVien[i].luong);
                }
                printf("---------------------------------------------------------------------------------------\n");
                head=head->next;
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

void freePhongBan(phongBan *head) {
    while (head != NULL) {
        phongBan *current = head;
        head = head->next;
        if (current->dsNhanVien != NULL) {
            free(current->dsNhanVien);
            current->dsNhanVien = NULL;
        }
        free(current);
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

// Ghi thong tin phong ban da cho ra van ban
void ghiThongTinPhongBan(phongBan *dsPhong, const char *filename) {
    if (!dsPhong) {
        printf("Khong co phong ban de ghi thong tin.\n");
        return;
    }
    printf("Danh sach phong ban:\n");
    phongBan *p = dsPhong;
    int idx = 0;
    while (p) {
        printf("%d. %s\n", ++idx, p->tenPB);
        p = p->next;
    }
    if (idx == 0) {
        printf("Khong co phong ban nao.\n");
        return;
    }
    int choice;
    do {
        printf("Chon phong ban muon ghi thong tin (1-%d): ", idx);
        scanf("%d", &choice);
        getchar();
    } while (choice < 1 || choice > idx);
    p = dsPhong;
    for (int i = 1; i < choice; i++)
        p = p->next;
    if (p->slNhanVien <= 0) {
        printf("Phong ban '%s' chua co nhan vien.\n", p->tenPB);
        return;
    }
    FILE *f = fopen(filename, "a");
    if (!f) {
        perror("Loi mo file");
        return;
    }
    fprintf(f, "===== PHONG BAN: %s =====\n\n", p->tenPB);
    for(int i = 0; i < p->slNhanVien; i++){
        fprintf(f, "----- Nhan vien thu %d -----\n", i + 1);
        fprintf(f, "Ma NV    : %s\n", p->dsNhanVien[i].maNV);
        fprintf(f, "Ho va ten: %s\n", p->dsNhanVien[i].hoTen);
        fprintf(f, "Ngay sinh: %s\n", p->dsNhanVien[i].ngaySinh);
        fprintf(f, "Gioi tinh: %s\n", p->dsNhanVien[i].gioiTinh);
        fprintf(f, "Ngay lam : %s\n", p->dsNhanVien[i].ngayLam);
        fprintf(f, "Luong    : %.2f\n", p->dsNhanVien[i].luong);
        fprintf(f, "---------------------------\n\n");
    }
    fclose(f);
    printf("Da ghi thong tin phong ban '%s' (%d NV) vao file %s\n",p->tenPB, p->slNhanVien, filename);
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
                                fprintf(f,"[%d]. Ngay %s - Ca %s - (%s - %s)\n",dem,tc->ngayTangCa,tc->caTang,tc->batDau,tc->ketThuc);
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
                                fprintf(f,"[%d]. Ngay %s - Ca %s - (%s - %s)\n",dem,ln->ngayNghi,ln->caNghi,ln->batDau,ln->ketThuc);
                                ln=ln->next;
                                dem++;
                        }
                }
                fprintf(f,"-------------------------------------------------\n");
        }
        fclose(f);
}
//ham doc du lieu tin file luu thong tin tat ca nhan vien
void DocFileDanhSachNhanVien(NhanVien *nv, int m, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Khong mo duoc file %s\n", filename);
        return;
    }
    char buffer[256];
    fgets(buffer, sizeof(buffer), f);
    for (int i = 0; i < m; i++) {
        fgets(buffer, sizeof(buffer), f);
        fgets(buffer, sizeof(buffer), f); sscanf(buffer, "Ma NV    : %[^]", nv[i].maNV);
        fgets(buffer, sizeof(buffer), f); sscanf(buffer, "Ho va ten: %[^]", nv[i].hoTen);
        fgets(buffer, sizeof(buffer), f); sscanf(buffer, "Ngay sinh: %[^]", nv[i].ngaySinh);
        fgets(buffer, sizeof(buffer), f); sscanf(buffer, "Gioi tinh: %[^]", nv[i].gioiTinh);
        fgets(buffer, sizeof(buffer), f); sscanf(buffer, "Ngay lam : %[^]", nv[i].ngayLam);
        fgets(buffer, sizeof(buffer), f); sscanf(buffer, "Luong    : %f", &nv[i].luong);
        fgets(buffer, sizeof(buffer), f);
        fgets(buffer, sizeof(buffer), f);
    }
    fclose(f);
    printf("Da doc thong tin cua %d nhan vien tu file %s\n", m, filename);
}
//ham doc file phong ban
void docFilePhongBan(phongBan *dsPhong, const char *filename) {
    if (!dsPhong) {
        printf("Khong co phong ban de ghi thong tin.\n");
        return;
    }
    printf("Danh sach phong ban:\n");
    phongBan *p = dsPhong;
    int idx = 0;
    while (p) {
        printf("%d. %s\n", ++idx, p->tenPB);
        p = p->next;
    }
    if (idx == 0) {
        printf("Khong co phong ban nao.\n");
        return;
    }
    int choice;
    do {
        printf("Chon phong ban muon ghi thong tin (1-%d): ", idx);
        scanf("%d", &choice);
        getchar();
    } while (choice < 1 || choice > idx);
    p = dsPhong;
    for (int i = 1; i < choice; i++) p = p->next;
    if (p->slNhanVien <= 0) {
        printf("Phong ban '%s' chua co nhan vien.\n", p->tenPB);
        return;
    }
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Loi mo file !\n");
        return;
    }
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), f)) {
        sscanf(buffer, "===== PHONG BAN: %[^\n=] =", p->tenPB);
        p->tenPB[strcspn(p->tenPB, "\n")] = '\0';
    }
    for (int i = 0; i < p->slNhanVien; i++) {
        fscanf(f, "----- Nhan vien thu %*d -----\n");
        fscanf(f, "Ma NV    : %[^\n]\n", p->dsNhanVien[i].maNV);
        fscanf(f, "Ho va ten: %[^\n]\n", p->dsNhanVien[i].hoTen);
        fscanf(f, "Ngay sinh: %[^\n]\n", p->dsNhanVien[i].ngaySinh);
        fscanf(f, "Gioi tinh: %[^\n]\n", p->dsNhanVien[i].gioiTinh);
        fscanf(f, "Ngay lam : %[^\n]\n", p->dsNhanVien[i].ngayLam);
        fscanf(f, "Luong    : %f\n", &p->dsNhanVien[i].luong);
        fgets(buffer, sizeof(buffer), f);
        fgets(buffer, sizeof(buffer), f);
    }
    fclose(f);
    printf("Da doc thong tin phong ban '%s' (%d NV) tu file %s\n", p->tenPB, p->slNhanVien, filename);
}
//ham doc thong tin ca lam cua tat ca nhan vien
void docThongTinLichLam(NhanVien *ds, int soLuong, const char *tenTep) {
    FILE *tep = fopen(tenTep, "r");
    if (!tep) {
        printf("Khong the mo tep %s!\n", tenTep);
        return;
    }
    char dong[256];
    while (fgets(dong, sizeof(dong), tep)) {
        char hoTen[50], maNV[12];
        if (sscanf(dong, "Nhan vien: %[^|]| Ma NV: %s", hoTen, maNV) != 2) {
            continue;
        }
        NhanVien *nvTarget = NULL;
        for (int i = 0; i < soLuong; i++) {
            if (strcmp(ds[i].maNV, maNV) == 0) {
                nvTarget = &ds[i];
                break;
            }
        }
        if (!nvTarget) {
            while (fgets(dong, sizeof(dong), tep) && strncmp(dong, "-------------------------------------------------", 10) != 0);
            continue;
        }
        nvTarget->LichLam = NULL;
        nvTarget->tangCa = NULL;
        nvTarget->lichNghi = NULL;
        if (!fgets(dong, sizeof(dong), tep)) break;
        if (!fgets(dong, sizeof(dong), tep)) break;
        LichLam *cuoiLL = NULL;
        if (strncmp(dong, "Khong co", 8) != 0) {
            do {
                if (dong[0] != '[') break;
                LichLam *moi = (LichLam *)malloc(sizeof(LichLam));
                if (!moi) break;
                sscanf(dong, "[%*d]. Ca %s - (%[^)] - %[^)])", moi->caLam, moi->batDau, moi->ketThuc);
                moi->caLam[strcspn(moi->caLam, "\n")] = '\0';
                moi->next = NULL;
                if (!cuoiLL) nvTarget->LichLam = cuoiLL = moi;
                else cuoiLL = cuoiLL->next = moi;
            } while (fgets(dong, sizeof(dong), tep));
        } else {
            fgets(dong, sizeof(dong), tep);
        }
        if (strncmp(dong, "Lich tang ca:", 13) != 0) fgets(dong, sizeof(dong), tep);
        tangCa *cuoiTC = NULL;
        if (strncmp(dong, "Khong co", 8) != 0) {
            do {
                if (dong[0] != '[') break;
                tangCa *moi = (tangCa *)malloc(sizeof(tangCa));
                if (!moi) break;
                sscanf(dong, "[%*d]. Ngay %s - Ca %s - (%[^)] - %[^)])", moi->ngayTangCa, moi->caTang, moi->batDau, moi->ketThuc);
                moi->caTang[strcspn(moi->caTang, "\n")] = '\0';
                moi->next = NULL;
                if (!cuoiTC) nvTarget->tangCa = cuoiTC = moi;
                else cuoiTC = cuoiTC->next = moi;
            } while (fgets(dong, sizeof(dong), tep));
        } else {
            fgets(dong, sizeof(dong), tep);
        }
        if (strncmp(dong, "Lich nghi:", 10) != 0) fgets(dong, sizeof(dong), tep);
        lichNghi *cuoiLN = NULL;
        if (strncmp(dong, "Khong co", 8) != 0) {
            do {
                if (dong[0] != '[') break;
                lichNghi *moi = (lichNghi *)malloc(sizeof(lichNghi));
                if (!moi) break;
                sscanf(dong, "[%*d]. Ngay %s - Ca %s - (%[^)] - %[^)])", moi->ngayNghi, moi->caNghi, moi->batDau, moi->ketThuc);
                moi->caNghi[strcspn(moi->caNghi, "\n")] = '\0';
                moi->next = NULL;
                if (!cuoiLN) nvTarget->lichNghi = cuoiLN = moi;
                else cuoiLN = cuoiLN->next = moi;
            } while (fgets(dong, sizeof(dong), tep));
        }
        while (fgets(dong, sizeof(dong), tep)) {
            if (strncmp(dong, "-------------------------------------------------", 10) == 0)
                break;
        }
    }
    fclose(tep);
    printf("Da doc file lich lam %s thanh cong.\n", tenTep);
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
//ham thay doi thong tin nhan vien phong ban
void thayDoiThongTinNhanVienPhongBan(phongBan **head, char *maNv ,NhanVien *nv,int m){
        if(*head==NULL){
                printf("Chua co phong ban nao !\n");
                return;
        }
        phongBan *temp=*head;
        while(temp!=NULL){
                if(temp->dsNhanVien==NULL||temp->slNhanVien==0){
                        temp=temp->next;
                        continue;
                }
                for(int i=0;i<temp->slNhanVien;i++){
                        if(strcmp(temp->dsNhanVien[i].maNV,maNv)==0){
                                printf("Nhap thong tin moi:\n");
                                printf("Nhap ho ten: ");
                                fgets(temp->dsNhanVien[i].hoTen,sizeof(temp->dsNhanVien[i].hoTen),stdin);
                                temp->dsNhanVien[i].hoTen[strcspn(temp->dsNhanVien[i].hoTen,"\n")]='\0';
                                printf("Gioi tinh: ");
                                fgets(temp->dsNhanVien[i].gioiTinh,sizeof(temp->dsNhanVien[i].gioiTinh),stdin);
                                temp->dsNhanVien[i].gioiTinh[strcspn(temp->dsNhanVien[i].gioiTinh,"\n")]='\0';
                                printf("Nhap ngay sinh (vd: 09/11/2006): ");
                                fgets(temp->dsNhanVien[i].ngaySinh,sizeof(temp->dsNhanVien[i].ngaySinh),stdin);
                                temp->dsNhanVien[i].ngaySinh[strcspn(temp->dsNhanVien[i].ngaySinh,"\n")]='\0';
                                printf("Nhap ngay lam (vd: 09/11/2006): ");
                                fgets(temp->dsNhanVien[i].ngayLam,sizeof(temp->dsNhanVien[i].ngayLam),stdin);
                                temp->dsNhanVien[i].ngayLam[strcspn(temp->dsNhanVien[i].ngayLam,"\n")]='\0';
                                printf("Nhap ma nhan vien: ");
                                fgets(temp->dsNhanVien[i].maNV,sizeof(temp->dsNhanVien[i].maNV),stdin);
                                temp->dsNhanVien[i].maNV[strcspn(temp->dsNhanVien[i].maNV,"\n")]='\0';
                                printf("Luong: ");
                                scanf("%f",&temp->dsNhanVien[i].luong);
                                getchar();
                                for(int j=0;j<m;j++){
                                        if(strcmp(nv[j].maNV,maNv)==0){
                                                strcpy(nv[j].hoTen,temp->dsNhanVien[i].hoTen);
                                                strcpy(nv[j].gioiTinh,temp->dsNhanVien[i].gioiTinh);
                                                strcpy(nv[j].ngaySinh,temp->dsNhanVien[i].ngaySinh);
                                                strcpy(nv[j].ngayLam,temp->dsNhanVien[i].ngayLam);
                                                strcpy(nv[j].maNV,temp->dsNhanVien[i].maNV);
                                                nv[j].luong=temp->dsNhanVien[i].luong;
                                                printf("Da cap nhan thong tin.\n");
                                                return;
                                        }
                                }
                        }
                }
                temp=temp->next;
        }
        if(temp==NULL)
                printf("Khong tim thay nhan vien !");
}
//ham thong ke nhan vien co ki luat cao nhan cua tung phong ban
void thongKeKyLuatPhongBan(phongBan *dsPhong, int thang, int nam) {
    while (dsPhong != NULL){
        if (dsPhong->dsNhanVien == NULL || dsPhong->slNhanVien == 0){
            printf("\nPhong ban '%s' khong co nhan vien!\n", dsPhong->tenPB);
            dsPhong = dsPhong->next;
            continue;
        }
        printf("\n=== PHONG BAN: %s ===\n", dsPhong->tenPB);
        float lech1 = -99999;
        float lech2 = 99999;
        int test1 = -1, test2 = -1;
        for (int i = 0; i < dsPhong->slNhanVien; i++){
            NhanVien nv = dsPhong->dsNhanVien[i];
            float gioThucTe = tinhGioLam(nv, thang, nam);
            if (gioThucTe == 0) continue;
            float gioCoDinh = tinhGioLamCoDinh(nv);
            float lech = gioThucTe - gioCoDinh;
            if (lech >= 0 && lech > lech1) {
                lech1 = lech;
                test1 = i;
            }
            if (lech < 0 && lech < lech2) {
                lech2 = lech;
                test2 = i;
            }
        }
        if (test1 != -1){
            NhanVien nv = dsPhong->dsNhanVien[test1];
            printf("-> Nhan vien lam vuot gio nhieu nhat: %s (Ma: %s)\n", nv.hoTen, nv.maNV);
            printf("   Gio lam thuc te: %.2f | Gio lam co dinh: %.2f | Lech: +%.2f\n",
                   tinhGioLam(nv, thang, nam), tinhGioLamCoDinh(nv), lech1);
        } else {
            printf("-> Khong co nhan vien lam vuot gio.\n");
        }
        if (test2 != -1){
            NhanVien nv = dsPhong->dsNhanVien[test2];
            printf("-> Nhan vien lam thieu gio nhieu nhat: %s (Ma: %s)\n", nv.hoTen, nv.maNV);
            printf("   Gio lam thuc te: %.2f | Gio lam co dinh: %.2f | Lech: %.2f\n",
                   tinhGioLam(nv, thang, nam), tinhGioLamCoDinh(nv), lech2);
        } else {
            printf("-> Tat ca nhan vien deu lam dung gio hoac vuot gio.\n");
        }
        dsPhong = dsPhong->next;
    }
}

int main() {
    NhanVien *Nv = NULL;
    int m = 0;
    phongBan *dsPhongBan = NULL;
    NhanVien *NvNam = NULL, *NvNu = NULL;
    int demNam = 0, demNu = 0;
    int choice;
    do {
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
        printf("| 9. Ghi va doc thong tin tat ca nhan vien ra file              |\n");
        printf("|---------------------------LICH LAM----------------------------|\n");
        printf("| 10. Nhap lich lam co dinh cho nhan vien                       |\n");
        printf("| 11. Them ca lam co dinh moi cho mot nhan vien                 |\n");
        printf("| 12. Cap nhat/Xoa lich lam co dinh cho nhan vien               |\n");
        printf("| 13. Dang ky lich tang ca cho nhan vien                        |\n");
        printf("| 14. Dang ky lich nghi cho nhan vien                           |\n");
        printf("| 15. In chi tiet lich lam tat ca nhan vien                     |\n");
        printf("| 16. In chi tiet lich lam mot nhan vien                        |\n");
        printf("| 17. Ghi va doc file lich lam cua tat ca nhan vien             |\n");
        printf("|---------------------------PHONG BAN---------------------------|\n");
        printf("| 18. Them phong ban moi                                        |\n");
        printf("| 19. Them nhan vien vao phong ban                              |\n");
        printf("| 20. cap nhat thong tin nhan vien cua phong ban                |\n");
        printf("| 21. Xoa thong tin nhan vien cua phong ban                     |\n");
        printf("| 22. Hien thi danh sach nhan vien theo phong ban               |\n");
        printf("| 23. Ghi thong tin phong ban ra file                           |\n");
        printf("| 24. Doc thong tin trong file da ghi thong tin phong ban       |\n");
        printf("| 25. Cap nhat thong tin moi cho phong ban                      |\n");
        printf("| 26. Thong ke nhan vien giu ki luat tot nhat o tung phong ban  |\n");
        printf("| 0. Thoat                                                      |\n");
        printf("|---------------------------------------------------------------|\n");
        printf("=================================================================\n");
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
                capNhatThongTinNhanVien(Nv, m,dsPhongBan);
                break;
            case 3:
                xoaNhanVien(Nv, &m,&dsPhongBan);
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
                if (demNam) inDanhSachNhanVien(NvNam, demNam);
                if (demNu) inDanhSachNhanVien(NvNu, demNu);
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
                DocFileDanhSachNhanVien(Nv, m, "tatca_nv.txt");
                printf("Da doc lai du lieu tu file!\n");
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
               docThongTinLichLam(Nv, m, "LichLam.txt");
                printf("Da doc lai lich lam tu file!\n");
                break;
            case 18:
                themPhongBan(&dsPhongBan);
                break;
            case 19:
                themNhanVienVaoPhongBan(&dsPhongBan, Nv, m);
                break;
             case 20: {
                char  tenPB[30];
                printf("Nhap ten phong ban: ");
                fgets(tenPB, sizeof(tenPB), stdin);
                tenPB[strcspn(tenPB, "\n")] = '\0';
                phongBan *temp=dsPhongBan;
                while(temp!=NULL){
                        if(strcasecmp(tenPB,temp->tenPB)==0){
                                break;
                        }
                        temp=temp->next;
                }
                if(temp==NULL){
                        printf("Khong tim ra phong ban !\n");
                        break;
                        }
                else{
                        char maNv[12];
                        printf("Nhap ma nhan vien muon cap nhat: ");
                        fgets(maNv, sizeof(maNv), stdin);
                        maNv[strcspn(maNv, "\n")] = '\0';
                        thayDoiThongTinNhanVienPhongBan(&dsPhongBan, maNv, Nv, m);
                        break;
                        }
                }
             case 21: {
                char maNv[12];
                printf("Nhap ma nhan vien muon xoa khoi phong ban: ");
                fgets(maNv, sizeof(maNv), stdin);
                maNv[strcspn(maNv, "\n")] = '\0';
                xoaThongTinNhanVienPhongBan(&dsPhongBan, maNv);
                break;
                }
             case 22:
                inDanhSachNhanVienCuaPhong(dsPhongBan);
                break;
             case 23:
                 ghiThongTinPhongBan(dsPhongBan, "phongban.txt");
                printf("Da ghi phong ban ra file phongban.txt\n");
                break;
             case 24:
                docFilePhongBan(dsPhongBan, "phongban.txt");
                printf("Da doc lai thong tin phong ban tu file!\n");
                break;
             case 25:
                capNhatThongTinNhanVienVaoPhongBan(Nv, m, dsPhongBan);
                break;
             case 26: {
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
                thongKeKyLuatPhongBan(dsPhongBan, thang,nam);
                break;
                }
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
        freePhongBan(dsPhongBan);
    printf("Chuong trinh ket thuc.\n");
    return 0;
}
