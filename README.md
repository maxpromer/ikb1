# iKB-1 Plugin for KidBrightIDE

ปลั๊กอินสำหรับบอร์ด iKB-1 ต่อขยายขาของบอร์ด KidBright32 ให้มีขาต่อใช้งาน-

 1. เซ็นเซอร์ / อุปกรณ์ดิจิตอลอินพุตเอาพุต / อุปกรณ์อนาล็อกเอาต์พุต จำนวน 8 ช่อง
 2. เซอร์โวมอเตอร์ รองรับรุ่น 180 องศา และ 360 องศา จำนวน 6 ช่อง
 3. มอเตอร์ ไดร์ภายใน 2 ช่อง และไดร์ภายนอกจำนวน 2 ช่อง
 4. Serial / UART / RS232 (TTL) จำนวน 1 ช่อง

![โครงสร้างบอร์ด iKB-1](https://sv1.picz.in.th/images/2018/12/21/9wPDr0.png)

## การติดตั้ง

### ติดตั้งจากตัวช่วยติดตั้ง

 1. ดาวน์โหลดไฟล์ปลั๊กอินได้ที่ส่วนดาวน์โหลด (อยู่ด้านล่างของหน้านี้)
 2. แตกไฟล์ zip ออกมา จะได้ไฟล์ชื่อ `Install iKB-1 Plugin.exe` ให้ดับเบิลคลิกเปิดไฟล์นี้
 3. อ่านคำแนะนำการติดตั้ง แล้วกด Extract เพื่อติดตั้งปลั๊กอิน หน้าต่างติดตั้งจะปิดอัตโนมัติเมื่อติดตั้งเสร็จแล้ว \* กรณีเคยติดตั้งไปแล้ว โปรแกรมจะให้ยืนยันเขียนไฟล์ทับ ให้ตอบ Yes
 4. เปิดโปรแกรม KidBrightIDE บล็อกจะอยู่ในเมนู ปลั๊กอิน > iKB-1

### ติดตั้งจาก Source code

Clone โค้ดต้นฉบับได้ที่ https://github.com/maxpromer/ikb_1_plugin จะได้โฟลเดอร์ ikb_1_plugin-master ให้แก้ชื่อเป็น ikb_1_plugin แล้วย้ายไปไว้ในโฟลเดอร์ `<ไดร์ที่ติดตั้ง Windows>\Users\<Username>\AppData\Local\KidBright\app-1.0.0\resources\app\kbide\plugins` เมื่อเปิดโปรแกรม KidBrightIDE บล็อกจะอยู่ใน ปลั๊กอิน > iKB-1

## การใช้งาน

ต่อบอร์ด iKB-1 เข้ากับบอร์ด KidBright32 ด้วยสาย KB Chain ที่แถมมาด้วย



## บล็อกอ่านค่าดิจิตอล

![บล็อก อ่านค่าดิจิตอล](https://sv1.picz.in.th/images/2018/12/21/9w2uXl.png)

ใช้อ่านค่าดิจิตอลจากช่อง 0 ถึง 7 (JST สีแดง) ให้ค่าออกมาเป็นตัวเลข 0, 1 และจริง เท็จตามลอจิกที่อ่านได้จริง ใช้งานกับบล็อกเงื่อนไข (if) และบล็อกไม่ (Not) ได้

**ตัวอย่างการนำไปใช้**

![โค้ดโปรแกรมแสดงรูปยิ้มเมื่อมีคนเดินผ่าน](https://sv1.picz.in.th/images/2018/12/21/9wCJyZ.png)

ใช้บล็อกนี้เพื่ออ่านค่าจาก PIR เซ็นเซอร์ - เมื่อ PIR ตรวจจับความเคลื่อนไหวได้ จะให้เอาต์พุตออกมาเป็นลอจิก 1 บล็อกอ่านค่าดิิจิตอล อ่านค่าได้ 1 จึงเข้าเงื่อนไข แล้วแสดงรูปยิ้มออกมาทางหน้าจอของบอร์ด KidBright

## บล็อกเขียนค่าดิิิจิตอล

![บล็อก เขียนค่าดิจิตอล](https://sv1.picz.in.th/images/2018/12/21/9wCMUl.png)

ใช้เขียนค่าลอจิก 0/1 หรือ จริง/เท็จ ไปที่ช่อง 0 ถึง 7 (ช่อง JST สีแดง) เพื่อสั่งงานอุปกรณ์ต่าง ๆ เช่น หลอด LED

**ตัวอย่างการนำไปใช้**

![โค้ดไฟวิ่ง 1](https://sv1.picz.in.th/images/2018/12/21/9w6YYz.png)

![โค้ดไฟวิ่ง 2](https://sv1.picz.in.th/images/2018/12/21/9w6zi8.png)

![โค้ดไฟวิ่ง 3](https://sv1.picz.in.th/images/2018/12/21/9w64uR.png)

ใช้บล็อกนี้เพื่อสั่งหลอด LED - ในวันคริสมาสต้องการให้หลอดไฟที่ต้นคริสมาสติดตามรูปแบบที่กำหนด จึงเขียนโปรแกรมสั่งให้หลอด LED ติดทีละดวงไปเรื่อย ๆ โดยดวงสุดท้ายติดอยู่ที่ดาวของต้นคลิสมาส จึงให้สว่างค้างนานกว่างดวงอื่น ๆ

## บล็อกอ่านค่าอนาล็อก

![บล็อกอ่านค่าอนาล็อก](https://sv1.picz.in.th/images/2018/12/21/9wnsZv.png)

ใช้อ่านค่าอนาล็อก ความละเอียด 10 บิต จากช่อง 0 ถึง 7 (ช่อง JST สีแดง) ให้ค่าออกมาเป็นตัวเลข 0 ถึง 1023

**ตัวอย่างการนำไปใช้**

![โค้ดเครื่องวัดความสุขของต้นไม้](https://sv1.picz.in.th/images/2018/12/21/9w81Ya.png)

ใช้บล็อกนี้กับเซ็นเซอร์วัดความชื้นในดิน - ต้องการสร้างเครื่องวัดความสุขของต้นไม้ จึงรวบรวมสิ่งที่บ่งบอกได้ว่าต้นไม้มีความสุข หนึ่งในนั้นคือความชื้นในดิน หากความชื้นในดินพอเหมาะ ก็จะทำให้ต้นไม้ได้รับสารอาหารเพียงพอ ส่งผลให้ต้นไม้มีความสุข

จึงใช้บล็อกอ่านค่าอนาล็อกอ่านค่าอนาล็อกจากเซ็นเซอร์ออกมา แล้วแปลงออกมาเป็นคะแนนความสุขของต้นไม้ 1 ถึง 5

## บล็อกควบคุมมอเตอร์

![บล็อกควบคุมมอเตอร์](https://sv1.picz.in.th/images/2018/12/21/9w85XP.png)

ใช้ควบคุมมอเตอร์ที่ต่อช่อง 1, 2 (ไดร์บนบอร์ด) และช่อง 3, 4 (ไดร์ภายนอก) ควบคุมทิศทาง หมุนตาม/หมุนทวน และควบคุมความเร็ว 0 ถึง 100%

**ตัวอย่างการนำไปใช้**

![โค้ดสั่งหุ่นยนต์หมุนรอบตัวเอง](https://sv1.picz.in.th/images/2018/12/21/9wVNlD.png)

ใช้ควบคุมการหมุนของล้อในหุ่นยนต์เดินตามเส้น - ต้องการให้หุ่นยนต์หมุนรอบตัวเอง 3 รอบ จึงใช้บล็อกควบคุมมอเตอร์ สั่งให้ล้อขวาไม่วิ่ง (ล้อขวาต่อกับมอเตอร์ และมอเตอร์ต่อกับช่องขับมอเตอร์ 1) และใช้บล็อกควบคุมมอเตอร์สั่งให้ล้อซ้ายหมุนตามเข็มที่ความเร็ว 50% ทดสอบหุ่นยนต์หมุน 1 รอบใช้เวลา 4 วินาที จึงหน่วงเวลา 3 รอบ * 4 วินาที = 12 วินาที

## บล็อกควบคุมเซอร์โวมอเตอร์ 180 องศา

![9wV8w1.png](https://sv1.picz.in.th/images/2018/12/21/9wV8w1.png)

ใช้ควบคุมเซอร์โว 180 องศา ที่ต่อช่อง 10 ถึง 15 (ในโปรแกรม ช่อง 1 คือช่อง 10) ให้หมุน 0 ถึง 200 องศา

**ตัวอย่างการนำไปใช้**

![9wXRA1.jpg](https://sv1.picz.in.th/images/2018/12/21/9wXRA1.jpg)

*ที่มา: https://blog.arduino.cc/2016/09/05/unlock-your-door-with-a-simple-hand-gesture/*

![โค้ดล็อกปรตูด้วยเซอร์โวมอเตอร์](https://sv1.picz.in.th/images/2018/12/21/9waQZe.png)

สั่งเซอร์โวมอเตอร์ให้ล็อกประตู - ต้องการสร้างกลอนล็อกประตูอิเล็กทรอนิกส์ พบว่ากลอนที่ใช้อยู่เป็นแบบเลื่อนล็อก จึงใช้เซอร์โวมอเตอร์มาต่อกับกลอนประตู ทดสอบการทำงานโดยกดปุ่ม S1 ให้ล็อกประตู และกดปุ่ม S2 ให้ปลดล็อก

ทดสอบสั่งงานมอเตอร์แล้ว หากต้องการให้ประตูล็อก ต้องสั่งใหเซอร์โวมอเตอร์หมุน 100 องศา และหากต้องการปลดล็อก ต้องสั่งให้หมุน 5 องศา จึงเขียนโปรแกรมเมื่อกดปุ่ม S1 ให้เซอร์โวหมุน 100 องศา และเมื่อกดปุ่ม S1 ให้เซอร์โวหมุน 5 องศา

## บล็อกควบคุมเซอร์โวมอเตอร์ 360 องศา

![บล็อกควบคุมเซอร์โวมอเตอร์ 360 องศา](https://sv1.picz.in.th/images/2018/12/21/9waoUQ.png)

ใช้ควบคุมเซอร์โวปรับแต่ง ที่ต่อช่อง 10 ถึง 15 (ในโปรแกรม ช่อง 1 คือช่อง 10) ให้ หมุนตาม/หมุนทวน และควบคุมความเร็ว 0 ถึง 100%

**ตัวอย่างการนำไปใช้**

![โค้ดสั่งให้หุ่นยนต์เดินหน้า 1 เมตร](https://sv1.picz.in.th/images/2018/12/21/9wvdhy.png)

ใช้ควบคุมเซอร์โวมอเตอร์ที่ต่อกับล้อของหุ่นยนต์ - ต้องการให้หุ่นยนต์ส่งของวิ่งไปที่จุดส่งของที่ห่างออกไป 1 เมตร ตัวหุ่นยนต์ใช้เซอร์โวมอเตอร์ 360 องศา เป็นตัวขับเคลื่อน ทดสอบแล้วที่ความเร็ว 100% ใช้เวลา 5 วินาที จะวิ่งได้ 1 เมตรพอดี ในโค้ดโปรแกรมจึงกำหนดให้เซอร์โวมอเตอร์หมุน 100% เป็นเวลา 5 วินาที

**หมายเหตุ** ในโค้ดให้หุ่นบนต์หมุนล้อเดียวเพื่อเป็นตัวอย่างเท่านั้น ความเป็นจริงต้องสั่งให้ล้อหมุน 2 ล้อพร้อมกัน หุ่นยนต์จึงจะวิ่งตรง

## บล็อกเกี่ยวกับการสื่อสารผ่าน Serial

บล็อกเกี่ยวการสื่อสารผ่าน Serial สามารถใช้งานได้กับโมดูลบลูทูธ HC-05 / HC-06 และโมดูลอื่นที่สื่อสารผ่าน Serial มีบล็อกให้ใช้งานดังนี้

### บล็อกตั้งค่า Baud rate

![บล็อกตั้งค่า Baud rate](https://sv1.picz.in.th/images/2018/12/21/9wv1zZ.png)

ใช้ตั้งค่า baud rate ของการรับ-ส่งข้อมูลผ่าน Serial สามารถตั้งได้ 9600/2400/57600 หรือ 115200

### บล็อกส่งข้อความ

![บล็อกส่งข้อความ](https://sv1.picz.in.th/images/2018/12/21/9wv5aN.png)

ใช้ส่งข้อความที่เป็น String ผ่าน Serial โดยมี 2 บล็อกให้เลือก คือส่งข้อมูลอย่างเดียว หรือส่งข้อมูลพร้อมขึ้นบรรทัดใหม่

### บล็อกอ่านข้อมูลที่รออ่านจากบัฟเฟอร์

![บล็อกอ่านข้อมูลที่รออ่านจากบัฟเฟอร์](https://sv1.picz.in.th/images/2018/12/21/9wvoWn.png)

บัฟเฟอร์เปรียบเสมือนที่เก็บข้อมูลชั่วคราว เมื่อมีการส่งข้อมูลมา ข้อมูลจะถูกเก็บลงบัฟเฟอร์ เมื่อต้องการอ่านข้อมูล จึงไปอ่านจากบัฟเฟอร์ บล็อกนี้ใช้อ่านจำนวนข้อมูลที่รออ่านจากบัฟเฟอร์ ให้ข้อมูลเป็นตัวเลข 0 ถึง 255

### บล็อกอ่านข้อมูลเป็น String

![บล็อกอ่านข้อมูลเป็น String](https://sv1.picz.in.th/images/2018/12/21/9wvjnS.png)

ใช้อ่านข้อมูลเป็นชุดแบบ String สามารถนำเอาต์พุตจากบล็อกนี้ ไปใส่บล็อก แอลอีดี 16x8 (ทุกบล็อก) ได้

**ตัวอย่างการนำไปใช้**

![9wGetW.png](https://sv1.picz.in.th/images/2018/12/21/9wGetW.png)

แสดงค่าอุณหภูมิบนแอพพลิเคชั่น รับ-ส่งข้อมูลด้วยบลูทูธโดยใช้ HC-05 - ศูนย์ข้อมูลหนึ่งต้องการมอนิเตอร์อุณหภูมิตลอดเวลา เพื่อตรวจสอบการทำงานของแอร์ เมื่อแอร์เสียเ้าหน้าที่สามารถสั่งปิดเครื่องเซอร์เวอร์ได้ เพื่อไม่ให้เกิดความเสียหายกับเครื่องเซิร์ฟเวอร์เมื่ออุณหภูมิสูงเกิน

จากความต้องการดังกล่าว หัวหน้าผู้ดูแลศูนย์ข้อมูลต้องการข้อมูลแบบทันที จึงใช้เซ็นเซอร์บนบอร์ด KidBright32 วัดอุณหภูมิ แล้วส่งข้อมูลผ่านบอร์ด iKB-1 ไปที่ HC-05 และข้อมูลจึงถูกส่งไปยังหัวหน้าผู้ดูแลศูนย์ข้อมูลแบบทันที

หัวหน้าผู้ดูแลศูนย์ข้อมูลต้องการทดสอบการทำงานของระบบที่ออกแบบขึ้น จึงให้บอร์ด KidBright32 แสดงผลข้อมูลที่รับได้จากบลูทูธด้วย

## ขีดจำกัดปัจจุบัน

 * อ่านค่าจาก Serial มากกว่า 6 - 8 ไบต์ไม่ได้
 * คำสั่งอ่านค่าจากบอร์ด จะทำงานช้ากว่าคำสั่งเขียน เพราะคำสั่งอ่านจะทำทีละคำสั่ง แต่คำสั่งเขียนจะทำพร้อมกับครั้งเดียว
 
## ผลกระทบเมื่อใช้งานกับปลั๊กอื่น

 * ปลั๊กอินนี้ เปลี่ยนความถี่ I2C เป็น 100kHz จึงอาจส่งผลต่อปลั๊กอินอื่น

## Source code

ปัจจุบันโค้ดต้นฉบับอยู่ที่ https://github.com/maxpromer/ikb_1_plugin นักพัฒนาท่านอื่นสามารถช่วยกันส่ง Pull Requests เข้ามาเพื่อปรับปรุงปลั๊กอินนี้ได้
