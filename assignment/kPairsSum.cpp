class Solution {
public:
    vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        
        vector<pair<int,int>> output;
        
        if(nums1.size()<=0 || nums2.size()<=0 || k<=0) return output;
        
        int second_size;
        second_size = nums2.size();
        
        int first_idx = 0;
        int second_idx = 0;
        vector<int> first_step(nums1.size(),0);
        vector<int> second_step(nums2.size(),0);
        int first_next;
        int second_next;
        int next_sum,pre_sum,min_sum,current_sum;
        int idx = 0;
        int min_idx;
        
        first_next = first_idx+1;
        second_next = second_idx+1;
        
        int another_time = 0;
        
        while(idx<k)
        {
                    // for(int j=0; j<=nums2.size(); j++ )
                    // {
                        
                    //     if(second_step[j] >= nums1.size()-1)
                    //     {
                    //         // output.push_back( make_pair(-11,-11) );
                    //         // output.push_back( make_pair(second_step[j],j) );
                    //         for(int i=0; i<nums1.size(); i++)
                    //         {
                    //             first_step[i]++;
                    //         }
                    //     }
                    // }
            
            
                    for(int i=0; i<=first_next; i++)
                    {
                        if(first_next < nums1.size())
                        {
                            if( first_step[i] < nums2.size() )
                            {
                                if(another_time==0)
                                {
                                    min_sum = nums1[i] + nums2[first_step[i]];
                                    min_idx = i;
                                    another_time = 1;
                                }
                                else
                                {
                                    current_sum = nums1[i] + nums2[first_step[i]];
                                    
                                    if(min_sum >= current_sum)
                                    {
                                        min_sum = current_sum;
                                        min_idx = i;
                                    }
                                }
                            }
                        }
                        else
                        {
                            if(i<=first_idx)
                            {
                                if( first_step[i] < nums2.size() )
                                {
                                    if(another_time==0)
                                    {
                                        min_sum = nums1[i] + nums2[first_step[i]];
                                        min_idx = i;
                                        another_time = 1;
                                    }
                                    else
                                    {
                                        current_sum = nums1[i] + nums2[first_step[i]];
                                        
                                        if(min_sum >= current_sum)
                                        {
                                            min_sum = current_sum;
                                            min_idx = i;
                                        }
                                    }
                                }
                            }
                        }
                        
                    }
            
            if(min_idx == first_next && first_next < nums1.size())
            {
                first_idx++;
                first_next++;
            }
            // else
            // {
            //     second_idx++;
            //     second_next++;
            // }
                if(another_time == 1)
                {
                    output.push_back( make_pair(nums1[min_idx],nums2[first_step[min_idx]]) );
                    first_step[min_idx]++;
                }
                idx++;
                
                
                
             
            
            another_time = 0;
            
        }
        
        // for(int i=0; i<first_next; i++)
        // {
        //     while( first_step[i] < nums2.size() )
        //     {
        //         output.push_back( make_pair(nums1[i],nums2[first_step[i]]) );
        //         first_step[i]++;
        //         idx++;
        //         if(idx>=k) break;
        //     }
        //     if(idx>=k) break;
        // }
        
        return output;
    }
};
