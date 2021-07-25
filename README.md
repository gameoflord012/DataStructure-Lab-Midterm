# DataStructure Lab Midterm
## contributors
1. Nguyễn Đức Mạnh
2. Thái Việt Nhật    
3. Hoàng Lượng
4. Trần Lạc Việt

## Requirements
- [ ] First, you will process the documents and store their content (i.e. words / tokens) in the data structures that you selected (in information retrieval, this phase is called indexing).

- [ ] Next, for every input query, you will process the query and search its keywords in the documents;

- [ ] For each such query, you will have to display the documents that satisfy the query.

- [ ] English stopwords should be removed if they appears in the queries. Link: http://www.ranks.nl/stopwords

- [ ] The search engine should support several operator such as:
    - [ ] AND
    - [ ] OR
    - [ ] Manchester –united 
    - [ ] intitle:hammer nails
    - [ ] Peanut Butter +and Jam
    - [ ] filetype:txt
    - [ ] Search for a price. Put $ in front of a number. For example: camera $400.
    - [ ] Search hashtags. Put # in front of a word. For example: #throwbackthursday
    - [ ] Search for an exact match. Put a word or phrase inside quotes. For example, "tallest building".
    - [ ] Search for wildcards or unknown words. Put a * in your word or phrase where you want to leave a placeholder. For example, "largest * in the world"
    - [ ] Search within a range of numbers. Put .. between two numbers. For example, camera $50..$100.
    - [ ] Entering “~set” will bring back results that include words like “configure”, “collection” and “change” which are all synonyms of “set

- [ ] History: list of queries that a user entered before. When the user enters one of these queries again, the search engine should suggest it. See auto suggestion feature in Google for inspiration.

## project structure
Chương trình gồm các phần chính sau:

### Data Structure
Nhiệm vụ là chứa dữ liệu vào cấu trúc, trả về kết quả khi truy vấn.

Data Structure phải hỗ trợ các toán tử sau:
    1. Cho các file dữ liệu và lưu nó vào cấu trúc dữ liệu
    2. Hỗ trợ các toán tử tìm kiếm như AND, OR, ..., được liệt kê trên 

### Input Processsor
Nhiệm vụ là phân tích cú pháp người dùng và đưa về cú pháp cơ bản để thực hiện truy vấn cho cấu trúc dữ liệu. Input Processor có khả năng lọc những stopwords trong cú pháp người nhập, đưa các toán tử AND, OR thành dạng cơ bản để thực hiện truy vấn DataStructure.

### User Interface
Nhiệm vụ của User Interface là đưa ra giao diện đẹp mắt cho người sử dụng. UI có khả năng xử lí kết quả của DataStructure thành dạng đẹp mắt cho người dùng. Cũng như có khả năng truyền tải dữ liệu từ người dùng cho Inputprocessor để phân tích
