package org.example.pojo;

import lombok.AllArgsConstructor;
import lombok.Builder;

@Builder
@AllArgsConstructor
public class User {

    private Integer id;
    private String password;
    private String postArticle;
    private String reviewArticle;
    private String publishedIssues;
    private String commentResponse;


    public User() {
    }

    /**
     * 获取
     * @return id
     */
    public Integer getId() {
        return id;
    }

    /**
     * 设置
     * @param id
     */
    public void setId(Integer id) {
        this.id = id;
    }

    /**
     * 获取
     * @return password
     */
    public String getPassword() {
        return password;
    }

    /**
     * 设置
     * @param password
     */
    public void setPassword(String password) {
        this.password = password;
    }

    /**
     * 获取
     * @return postArticle
     */
    public String getPostArticle(String postArticle) {
        return this.postArticle;
    }

    /**
     * 设置
     * @param postArticle
     */
    public void setPostArticle(String postArticle) {
        this.postArticle = postArticle;
    }

    /**
     * 获取
     * @return reviewArticle
     */
    public String getReviewArticle() {
        return reviewArticle;
    }

    /**
     * 设置
     * @param reviewArticle
     */
    public void setReviewArticle(String reviewArticle) {
        this.reviewArticle = reviewArticle;
    }

    /**
     * 获取
     * @return publishedIssues
     */
    public String getPublishedIssues() {
        return publishedIssues;
    }

    /**
     * 设置
     * @param publishedIssues
     */
    public void setPublishedIssues(String publishedIssues) {
        this.publishedIssues = publishedIssues;
    }

    /**
     * 获取
     * @return commentResponse
     */
    public String getCommentResponse() {
        return commentResponse;
    }

    /**
     * 设置
     * @param commentResponse
     */
    public void setCommentResponse(String commentResponse) {
        this.commentResponse = commentResponse;
    }

    public String toString() {
        return "User{id = " + id + ", password = " + password + ", postArticle = " + postArticle + ", reviewArticle = " + reviewArticle + ", publishedIssues = " + publishedIssues + ", commentResponse = " + commentResponse + "}";
    }

    public void getReviewArticle(String reviewArticle) {
    }

    public void getPublishedIssues(String publishedIssues) {
    }

    public void getCommentResponse(String commentResponse) {
    }
}