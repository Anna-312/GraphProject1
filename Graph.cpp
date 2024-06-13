void FindCenter(int mat[100][100], int n, int center[])
{
	int d[100][100];
	int e[100];
	int rad;
	int h = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (mat[i][j] == 1)
				if (i == j)
					d[i][j] = 0;
				else
					d[i][j] = 1;
			else
				d[i][j] = 100;
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (d[i][k] + d[k][j] < d[i][j])
					d[i][j] = d[i][k] + d[k][j];
	for (int i = 0; i < n; i++)
		e[i] = 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (d[i][j] > e[i])
				e[i] = d[i][j];
	rad = e[0];
	for (int i = 1; i < n; i++)
		if (e[i] < rad)
			rad = e[i];
	for (int i = 0; i < n; i++)
		if (e[i] == rad)
		{
			center[h] = i;
			h++;
		}
	center[h] = -1;
}

void FindCircle(int A[][100], int n, int rezMatr[100], int *rezlen, int center[])
{
	int St[100], M[100];
	for (int j = 0; j < 100; j++)   M[j] = 0;
	int* pSt = St;
	int* pM = M;
	int* pA = (int *)A;
	int* pR = rezMatr;
	int v, j, L, Pr, ks, vn;
	int* pC = center;
	FindCenter(A, n, center);
	vn = center[0];
	L = 0;
	M[vn] = 1;
	__asm {
		mov ks, 0
		mov ebx, pSt
		mov eax, vn
		mov [ebx], eax
		m1: cmp ks, 0
			js m2
			mov Pr, 0
			mov eax, ks
			mov ecx, 4
			mul ecx
			mov ebx, pSt
			add ebx, eax
			mov eax, [ebx]
			mov v, eax
			mov edx, L
			m3 : cmp edx, n
				jz afterfor
				mov j, edx
				mov eax, v
				mov ecx, 100
				mul ecx
				add eax, j
				mov ecx, 4
				mul ecx
				mov ebx, pA
				add ebx, eax
				mov eax, [ebx]
				cmp eax, 1
				jnz m4
				mov edx, j
				cmp edx, vn
				jnz m5
				cmp ks, 1
				jbe m4
				mov ebx, 0
				m6:
					cmp ebx, ks
					ja m7
					mov ecx, pSt
					mov eax, [ecx + 4 * ebx]
					mov ecx, pR
					mov [ecx + 4 * ebx], eax
					inc ebx
					jmp m6
				m7:
					mov ecx, vn
					mov eax, pR
					mov [eax + 4 * ebx], ecx
					add ks, 2
					mov eax, ks
					mov ecx, rezlen
					mov [ecx], eax
					jmp m2
				m5:
					mov ebx, pM
					mov eax, [ebx + 4 * edx]
					cmp eax, 0
					jnz m4
					mov Pr, 1
					jmp afterfor
			m4:
				mov edx, j
				inc edx
				jmp m3
			afterfor:
				cmp Pr, 1
				jnz m8
				inc ks
				mov ecx, ks
				mov eax, pSt
				mov [eax + 4 * ecx], edx
				mov L, 0
				mov eax, pM
				mov [eax + 4 * edx], 1
				jmp m1
				m8:
					mov eax, v
					mov L, eax
					inc L
					mov ebx, pM
					mov [ebx + 4 * eax], 0
					dec ks
					jmp m1
		m2:
	}
}