# PAT 示例代码

**二分查找**

```c++
				int left = 0;
                int right=end;
                while(left < right){
                    int mid=(left+right)>>1;
                    if(tail[mid]<nums[i]){
                        left = mid+1;
                    }
                    else{
                        right = mid;
                    }
                }
                tail[left]=nums[i];
```

