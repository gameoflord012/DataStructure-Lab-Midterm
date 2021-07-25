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
- [ ] User enters a keyword. The program displays top 5 results that highlights the keyword and the paragraph contains that keyword.

## Project Structure
Chương trình gồm các phần chính sau:

![Untitled Diagram (2)](https://user-images.githubusercontent.com/22610648/126887226-c97d9ebf-76bb-453c-ab66-fd1ae50d76e1.png)

### Data Structure
- Data Structure phải hỗ trợ các toán tử sau:
    1. Cho dữ liệu và lưu nó vào cấu trúc.
    2. Hỗ trợ các toán tử tìm kiếm như AND, OR, ... được liệt kê trên.
    3. Có khả năng lại lưu lịch sử truy vấn.

### Input Processsor
- Phân tích cú pháp người dùng và đưa cú pháp về dạng cơ bản để thực hiện truy vấn.
- Input Processor có khả năng lọc những stopwords trong cú pháp người nhập.

### Search Suggestion
- Lưu lại lịch sử nhập từ InputProcessor.
- Đưa ra những gợi ý từ dữ liệu đó.

### User Interface
- UI có khả năng xử lí kết quả truy vấn của DataStructure thành dạng đẹp mắt cho người dùng. 
- Có khả năng tải dữ liệu người nhập về Inputprocessor để phân tích.
- Hiện ra những từ gợi ý từ dữ liệu trong Search Suggestion.
