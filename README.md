# K-means & Gaussian Mixture Model Implementation
* KECE471 Computer Vision ([Prof. Chang-Su Kim](https://mcl.korea.ac.kr/))
* C++ Implementation of 1-dimensional K-means & Gaussian Mixture Model for gray-scale image segmentation

## Result
* The result of applying 1D K-means clustering & GMM method to each image with the number of clusters, $k$ = 2, 4, or 8, is as follows.
* Note that each cluster's pixel value is the average gray level.

### Original Input Image
`KU.raw` <br>
![image](https://user-images.githubusercontent.com/37537248/176437073-8a97e7d3-e0bd-40f6-b956-6aa2afe3d78a.png)
<br>

`Gundam.raw` <br>
![image](https://user-images.githubusercontent.com/37537248/176437159-b570b0c4-895f-4535-9044-a34fcf692f9e.png)
<br>

`Golf.raw` <br>
![image](https://user-images.githubusercontent.com/37537248/176437289-54816e4d-0d20-4cf3-80a3-6d78fb78c07d.png)
<br>

### 1D K-means Clustering
$k = 2$, `KU.raw` <br>
Image | Log
:---------------------:|:-------------------------:
![image](https://user-images.githubusercontent.com/37537248/176439142-fbbe0ad0-245f-40a1-b128-b48335a594fd.png) | ![image](https://user-images.githubusercontent.com/37537248/176439160-210c2ddf-d265-4f6f-963c-7931d0cffb8b.png)
<br>

$k = 4$, `KU.raw` <br>
Image | Log
:---------------------:|:-------------------------:
![image](https://user-images.githubusercontent.com/37537248/176440502-31eda6d3-168b-47e9-8a55-c132ae0ca7f8.png) | ![image](https://user-images.githubusercontent.com/37537248/176440476-947cb4ec-2f13-4dc8-8823-eb07e631b3f3.png)
<br>

$k = 8$, `KU.raw` <br>
Image | Log
:---------------------:|:-------------------------:
![image](https://user-images.githubusercontent.com/37537248/176440606-a7f241df-6865-479f-9ae2-99dd41a31403.png) | ![image](https://user-images.githubusercontent.com/37537248/176440622-df65892c-eaef-44a8-ad05-de9148bec5e4.png)
<br>

$k = 2$, `Gundam.raw` <br>
Image | Log
:---------------------:|:-------------------------:
![image](https://user-images.githubusercontent.com/37537248/176442531-26f37bac-6097-4f6b-90ef-a69b31253d78.png) | ![image](https://user-images.githubusercontent.com/37537248/176442552-01ab7b63-d929-4bc6-ac19-7cca6d01d829.png)
<br>

$k = 4$, `Gundam.raw` <br>
Image | Log
:---------------------:|:-------------------------:
![image](https://user-images.githubusercontent.com/37537248/176442812-eeeda07a-c308-471a-b10e-178e40350d3e.png) | ![image](https://user-images.githubusercontent.com/37537248/176442841-9c735561-32c7-4ff7-9585-3064a992b2fe.png)
<br>

$k = 8$, `Gundam.raw` <br>
Image | Log
:---------------------:|:-------------------------:
![image](https://user-images.githubusercontent.com/37537248/176442972-145072f8-7761-4d33-8ef7-03b14f7a42af.png) | ![image](https://user-images.githubusercontent.com/37537248/176442993-bcdde341-ae81-4ee0-ab81-375cd2e1e5d5.png)
<br>

$k = 2$, `Golf.raw` <br>
Image | Log
:---------------------:|:-------------------------:
![image](https://user-images.githubusercontent.com/37537248/176443317-352fac95-5e7e-4ed3-91e6-0eb386df822f.png) | ![image](https://user-images.githubusercontent.com/37537248/176443343-0ae646b8-958b-462a-907d-28720553d5c2.png)
<br>

$k = 4$, `Golf.raw` <br>
Image | Log
:---------------------:|:-------------------------:
![image](https://user-images.githubusercontent.com/37537248/176443456-0d49150d-9e1f-4de4-9759-23e8e1c5f5f5.png) | ![image](https://user-images.githubusercontent.com/37537248/176443468-9f174785-954f-41f0-b8ff-fa0ff4f7e081.png)
<br>

$k = 8$, `Golf.raw` <br>
Image | Log
:---------------------:|:-------------------------:
![image](https://user-images.githubusercontent.com/37537248/176443608-6b38db57-3b5e-43d4-98c0-223ade8826f7.png) | ![image](https://user-images.githubusercontent.com/37537248/176443617-a248c938-4063-4fe3-92d4-49dd4c08e3ab.png)
<br>

### Gaussian Mixture Model

$k = 2$, `KU.raw` <br>
Image | Log
:---------------------:|:-------------------------:
![image](https://user-images.githubusercontent.com/37537248/176444152-360c1f47-90b7-42fb-a6e6-70ddc4873aeb.png) | ![image](https://user-images.githubusercontent.com/37537248/176444162-cc3f1734-b332-4c03-90ba-e1d04d54ea7a.png)
<br>

$k = 4$, `KU.raw` <br>
Image | Log
:---------------------:|:-------------------------:
![image](https://user-images.githubusercontent.com/37537248/176444350-1ffea2d5-75b9-4ed1-bed1-ab6199c7bd38.png) | ![image](https://user-images.githubusercontent.com/37537248/176444359-c5854a80-ede4-448c-855b-ddc536a7cb67.png)
<br>

$k = 8$, `KU.raw` <br>
Image | Log
:---------------------:|:-------------------------:
![image](https://user-images.githubusercontent.com/37537248/176444536-74bde875-02cb-4429-81d2-442f65a8e58a.png) | ![image](https://user-images.githubusercontent.com/37537248/176444550-c82fda5b-3ecf-47a9-92c0-62f8172d9dd4.png)
<br>

$k = 2$, `Gundam.raw` <br>
Image | Log
:---------------------:|:-------------------------:
![image](https://user-images.githubusercontent.com/37537248/176444798-982a6b66-066b-4cf8-b549-3aa2d09f9394.png) | ![image](https://user-images.githubusercontent.com/37537248/176444824-c3494a50-38c0-426c-9907-90b2d1f43816.png)
<br>

$k = 4$, `Gundam.raw` <br>
Image | Log
:---------------------:|:-------------------------:
![image](https://user-images.githubusercontent.com/37537248/176444952-c59cbc50-796f-4381-9726-dafbc7d96e34.png) | ![image](https://user-images.githubusercontent.com/37537248/176444963-f1957435-3d9c-44e9-949d-eacc7d684f45.png)
<br>

$k = 8$, `Gundam.raw` <br>
Image | Log
:---------------------:|:-------------------------:
![image](https://user-images.githubusercontent.com/37537248/176445067-6973742c-d1b6-415f-a0ff-d4cb6f10ce71.png) | ![image](https://user-images.githubusercontent.com/37537248/176445081-1ebb96cd-20b9-435d-84e2-bf7275536d04.png)
<br>

$k = 2$, `Golf.raw` <br>
Image | Log
:---------------------:|:-------------------------:
![image](https://user-images.githubusercontent.com/37537248/176445164-7990700e-1dee-4e22-b812-4b2e664ceed5.png) | ![image](https://user-images.githubusercontent.com/37537248/176445185-ed51bd11-e04f-4a4d-bb31-f63d86577692.png)
<br>

$k = 4$, `Golf.raw` <br>
Image | Log
:---------------------:|:-------------------------:
![image](https://user-images.githubusercontent.com/37537248/176445285-01a7a980-3c1a-4c61-aff4-04ddf65a6473.png) | ![image](https://user-images.githubusercontent.com/37537248/176445301-21e6bf7f-c7bf-446a-befe-9e09755f234c.png)
<br>

$k = 8$, `Golf.raw` <br>
Image | Log
:---------------------:|:-------------------------:
![image](https://user-images.githubusercontent.com/37537248/176445425-aabb735d-4542-487d-9cd9-25fb98ae6429.png) | ![image](https://user-images.githubusercontent.com/37537248/176445438-618223d7-d553-4a39-875f-466b60b76edd.png)
<br>

