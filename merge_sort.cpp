#include <bits/stdc++.h>
using namespace std;
void merge(vector<int>& arr, int start, int mid, int end) {
 int len1 = mid - start + 1;
 int len2 = end - mid;
 vector<int> arr1(len1, 0);
 vector<int> arr2(len2, 0);
 int pos = start;
 for (int i = 0; i < len1; i++) {
 arr1[i] = arr[pos++];
 }
 pos = mid + 1;
 for (int i = 0; i < len2; i++) {
 arr2[i] = arr[pos++];
 }
 int i = 0, j = 0;
 pos = start;
 while (i < len1 && j < len2) {
 if (arr1[i] <= arr2[j]) {
 arr[pos++] = arr1[i++];
 } else {
 arr[pos++] = arr2[j++];
 }
 }
 while (i < len1) {
 arr[pos++] = arr1[i++];
 }
 while (j < len2) {
 arr[pos++] = arr2[j++];
 }
}
void mergeSort(vector<int>& arr, int start, int end) {
 if (start >= end) {
 return;
 }
 int mid = start + (end - start) / 2;
 mergeSort(arr, start, mid);
 mergeSort(arr, mid + 1, end);
 merge(arr, start, mid, end);
}
int main() {
 int N;
 cin >> N;
 vector<int> arr(N);
 for (int i = 0; i < N; i++) {
 cin >> arr[i];
 }
 mergeSort(arr, 0, N - 1);
 for (int i = 0; i < N; i++) {
 cout << arr[i] << " ";
 }
 return 0;
}
