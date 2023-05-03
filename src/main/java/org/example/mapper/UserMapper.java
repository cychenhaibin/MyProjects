package org.example.mapper;

import org.apache.ibatis.annotations.Param;
import org.example.pojo.User;

import java.util.List;
import java.util.Map;

public interface UserMapper {




    List<User> selectAll();

    // 条件查询
    //List<User> selectByCondition(@Param("id")int id,@Param("postArticle") String postArticle,@Param("reviewArticle") String reviewArticle,@Param("publishedIssues") String publishedIssues,@Param("commentResponse") String commentResponse);
    //List<User> selectByCondition(User user);
    List<User> selectByCondition(User user);


}
