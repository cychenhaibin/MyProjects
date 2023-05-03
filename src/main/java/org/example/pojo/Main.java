package org.example.pojo;

import com.alibaba.druid.pool.DruidDataSourceFactory;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;
import org.example.mapper.UserMapper;
import org.example.pojo.User;

import javax.sql.DataSource;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.List;
import java.util.Properties;
import java.util.Scanner;

        /*
        注册登录模块
        1.注册
            1.1新增用户数据到数据库
            1.2注册新用户时需要检测数据库中是否存在同名用户
        2.登录
            2.1在数据库中检验账号和密码是否准确
        3.修改密码
            3.1根据用户名和密码进行匹配，更新密码
        4.注销
            4.1根据用户信息在数据库中删除记录

        数据库设计
        1.字段（id：主键，不为空，varchar，账号），password（不为空，varchar，密码）
         */

public class Main {
    // 主函数
    public static void main(String[] args) throws Exception{


        // 注册驱动
        //Class.forName("com.mysql.cj.jdbc.Driver");
        System.out.println("连接数据库成功！");
        //String url = "jdbc:mysql://localhost:3306/item"; // 提示：(jdbc:mysql://localhost:3306/数据库名字)
        //String user = "root";                            //提示：sql用户名
        //String dbpassword = "chb20040728";               //提示：sql密码
        // 获取连接
        //Connection conn= DriverManager.getConnection(url,user,dbpassword);
        //System.out.println("成功加载数据库"+conn);


        // 连接池
        // 加载配置文件
        Properties prop=new Properties();
        prop.load(new FileInputStream("druid.properties"));
        // 获取连接池对象
        DataSource dataSource= DruidDataSourceFactory.createDataSource(prop);
        // 获取数据库连接
        Connection conn=dataSource.getConnection();
        System.out.println("---------------------------------------------");
        System.out.println("********       欢迎进入知乎       ********");
        System.out.println("注册请输入1， 登录请输入2， 修改密码请输入3， 注销请输入4， 查询信息输入5");
        System.out.println("请输入功能序号：");
        Scanner sc=new Scanner(System.in);
        int flag=sc.nextInt();
        System.out.println("----------------------------------------------");
        if (flag==1){
            // 注册
            System.out.println("请输入账号：");
            String id = sc.next();
            System.out.println("请输入密码：");
            String password = sc.next();
            signup(conn,id,password);
        }
        else if (flag==2){
            // 登录
            System.out.println("请输入账号：");
            String id = sc.next();
            System.out.println("请输入密码：");
            String password = sc.next();
            login(conn,id,password);
        }
        else if (flag==3){
            // 修改密码
            System.out.println("请输入账号：");
            String id = sc.next();
            System.out.println("请输入旧密码：");
            String oldpassword = sc.next();
            System.out.println("请输入新密码：");
            String newpassword = sc.next();
            changePassword(conn,id,oldpassword,newpassword);
        }
        else if (flag==4){
            // 注销
            System.out.println("请输入账号：");
            String id = sc.next();
            System.out.println("请输入密码：");
            String password = sc.next();
            deleteUser(conn,id,password);

        }
        else if(flag==5){
            checkUser(conn);
        }
        else {
            System.out.println("输入有误，请重新输入");
        }
        System.out.println("请输入你要查询：");
        Scanner sca = new Scanner(System.in);
        String postArticle = sca.next();
        // 处理参数
        postArticle = "%" + postArticle + "%";
        // 封装对象
        User user = new User();
        //user.getId(id);
        user.getPostArticle(postArticle);

        // 获取SqlSessionFactory
        // 加载mybatis的核心配置文件，获取SqlSessionFactory
        String resource = "mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resource);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);

        // 获取SqlSessionFactory对象
        SqlSession sqlSession = sqlSessionFactory.openSession();

        // 获取Mapper接口代表对象
        UserMapper userMapper = sqlSession.getMapper(UserMapper.class);

        // 执行方法

        List<User> users = userMapper.selectByCondition(user);
        System.out.println(user);
        //释放资源
        sqlSession.close();


    }


    // 注册模块（增加）
    public static void signup(Connection conn,String id,String password)throws Exception{

        Class.forName("com.mysql.cj.jdbc.Driver");
        System.out.println("加载成功");
        // 将sql指令 发送给服务器执行
        // 获取Statement对象
        Statement statement = conn.createStatement();
        // 定义sql
        String sql1 = "select id from user where id=?";
        // select 列名 from 表名 where 列名=?
        PreparedStatement PS = conn.prepareStatement(sql1);
        PS.setString(1,id);//给sql语句的第1个问号赋值

        ResultSet res = PS.executeQuery();
        if (res.next()){
            System.out.println("该账号已存在，请重新输入！");
        }else{
            String sql2="insert into user (id,password) values(?,?);";
            // insert into 表名 (列名1,列名2) values(?,?);
            PS=conn.prepareStatement(sql2);
            PS.setString(1,id);//给第1个问号赋值
            PS.setString(2,password);//给第2个问号赋值
            PS.executeUpdate();
            System.out.println("注册成功");
        }
        // 关闭所有接口
        res.close();
        PS.close();
        statement.close();
        conn.close();
    }

    // 登录模块（查询）
    public static void login(Connection conn,String id,String password) throws Exception{
        String sql1 = " select id from user where id=? ";
        // 将sql指令发送给服务器执行
        PreparedStatement PS = conn.prepareStatement(sql1);
        PS.setString(1,id);
        ResultSet res = PS.executeQuery();
        if(res.next()){
            //预编译sql
            String sql2 = "select * from user where id= ? and password= ?";
            PreparedStatement PS1 = conn.prepareStatement(sql2);
            PS1.setString(1,id);
            PS1.setString(2,password);
            ResultSet res1 = PS1.executeQuery();
            if (res1.next()){
                System.out.println("登录成功！");
            } else {
                System.out.println();
                System.out.println(res1.next());
                System.out.println("密码错误");
            }
        }else {
            System.out.println("此账号还未注册，请先注册再登录！");
        }
        // 关闭连接
        conn.close();
        PS.close();
        res.close();
    }


    // 修改密码（修改）
    public static void changePassword(Connection conn,String id,String oldpassword,String newpassword) throws Exception{
        String sql1 = " select id from user where id=? ";
        // 将sql指令发送给服务器执行
        PreparedStatement PS = conn.prepareStatement(sql1);
        PS.setString(1,id);
        ResultSet res = PS.executeQuery();
        if(res.next()){
            String sql2 = " select * from user where id= ? and password= ?";
            PreparedStatement PS1 = conn.prepareStatement(sql2);
            PS1.setString(1,id);
            PS1.setString(2,oldpassword);
            ResultSet res1 = PS1.executeQuery();
            if (res1.next()){
                String updatesql1 = "update user set password = ? where id = ?";//定义要执行的sql语句
                PreparedStatement PS2=conn.prepareStatement(updatesql1);//在sql里执行语句
                PS2.setString(1,newpassword);
                PS2.setString(2,id);
                PS2.executeUpdate();//执行更新
                System.out.println("修改成功！");
            } else {
                System.out.println();
                System.out.println("密码错误");
            }
        }else {
            System.out.println("此用户名还未注册，请先注册再登录！");
        }
        conn.close();
        PS.close();
        res.close();


    }

    // 注销（删除）
    public static void deleteUser(Connection conn,String id,String password) throws Exception{
        String sql1 = " select id from user where id=? ";
        // 将sql指令发送给服务器执行
        PreparedStatement PS = conn.prepareStatement(sql1);
        PS.setString(1,id);
        ResultSet res = PS.executeQuery();
        if(res.next()){
            String sql2 = " select * from user where id= ? and password= ?";
            PreparedStatement PS1 = conn.prepareStatement(sql2);
            PS1.setString(1,id);
            PS1.setString(2,password);
            ResultSet res1 = PS1.executeQuery();
            if (res1.next()){
                System.out.println("登录成功！");
                String deletesql = "delete from user where id = ?";
                PreparedStatement PS2=conn.prepareStatement(deletesql);//在sql里执行语句
                PS2.setString(1,id);
                PS2.executeUpdate();
                System.out.println("删除成功！");
                PS2.close();
                res1.next();
            } else {
                System.out.println();
                System.out.println(res1.next());
                System.out.println("密码错误");
            }
        }else {
            System.out.println("此账号还未注册，请先注册再登录！");
        }
        conn.close();
        PS.close();
        res.close();
    }

    /*public static void checkUser(Connection conn) throws Exception {
        // 定义sql
        String sql = "select * from user";
        // 获取PS对象
        PreparedStatement PS = conn.prepareStatement(sql);
        // 设置参数

        // 执行参数
        ResultSet res = PS.executeQuery();
        // 处理结果
        //User user = null;
        List<User> users = new ArrayList<>();
        while(res.next()){
            // 获取数据
            int id=res.getInt("id");
            String password = res.getString("password");
            // 封装User对象
            User user = new User();
            user.setId(id);
            user.setPassword(password);
            // 装到集合里
            users.add(user);
        }
        System.out.println(users);
        // 释放资源
        res.close();
        PS.close();
        conn.close();
    }
    */



    public static void checkUser(Connection conn) throws Exception {
        // 获取SqlSessionFactory
        // 加载mybatis的核心配置文件，获取SqlSessionFactory
        String resource = "mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resource);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);

        // 获取SqlSessionFactory对象
        SqlSession sqlSession = sqlSessionFactory.openSession();

        // 获取Mapper接口代表对象
        UserMapper userMapper = sqlSession.getMapper(UserMapper.class);

        // 执行方法
        List<User> users = userMapper.selectAll();
        System.out.println(users);

        //释放资源
        sqlSession.close();
    }


    /*public static void testSelectByCondition() throws IOException {

        Scanner sca = new Scanner(System.in);
        System.out.println("请输入你要查询：");
        String postArticle = sca.next();
        // 处理参数
        postArticle = "%" + postArticle + "%";

        // 封装对象
        User use = new User();
        use.getPostArticle(postArticle);
        // 获取SqlSessionFactory
        // 加载mybatis的核心配置文件，获取SqlSessionFactory
        String resource = "mybatis-config.xml";
        InputStream inputStream = Resources.getResourceAsStream(resource);
        SqlSessionFactory sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);

        // 获取SqlSessionFactory对象
        SqlSession sqlSession = sqlSessionFactory.openSession();

        // 获取Mapper接口代表对象
        UserMapper userMapper = sqlSession.getMapper(UserMapper.class);

        // 执行方法
        User user=null;
        List<User> users = userMapper.selectByCondition(user);
        System.out.println(user);
        //释放资源
        sqlSession.close();


    }

     */



}