#include<iostream>
#include<cstring>

using namespace std;

enum format{mp3, wav, ogg, flac};
enum kompresija{x264, Theora, AV1};

class MediaSegment{
protected:
    char naslov[100];
    char avtor [100];
    int traenje;
    int golemina;
public:
MediaSegment(char *naslov="", char *avtor="", int traenje=0, int golemina=0){
    strcpy(this->naslov, naslov);
    strcpy(this->avtor, avtor);
    this->traenje=traenje;
    this->golemina=golemina;
}
virtual float price() const=0;
};
class AudioRecording : virtual public MediaSegment{
protected:
    format type;
    short channels;
public:
    AudioRecording (char *naslov="", char *avtor="", int traenje=0, int golemina=0, int type=0, short channels=0) :
        MediaSegment(naslov,avtor,traenje, golemina){
            this->type=(format)type;
            this->channels=channels;
        }
    float price()const{
        if (type==flac) return 1.5*traenje*channels;
        return traenje*channels;
    }
    friend ostream &operator << (ostream &o, const AudioRecording &a){
        o<<a.naslov<<" - "<<a.avtor<<" - "<<a.traenje<<" - "<<a.golemina<<" - "<<a.price()<<endl;
        return o;
    }
};
class VideoRecording: virtual public MediaSegment{
protected:
    int sirina;
    kompresija komp;
public:
    VideoRecording (char *naslov="", char *avtor="", int traenje=0, int golemina=0, int sirina=0, int komp=0) :
        MediaSegment(naslov,avtor,traenje, golemina){
            this->komp=(kompresija)komp;
            this->sirina=sirina;
        }
    float price() const{
        float cena;
        if (sirina<=1920)
            cena=100*traenje;
        else
            cena=170*traenje;
        if (komp==Theora) return 0.9*cena;
        if (komp==x264) return 1.5*cena;
        return cena;
    }
    friend ostream &operator << (ostream &o, const VideoRecording &v){
        o<<v.naslov<<" - "<<v.avtor<<" - "<<v.traenje<<" - "<<v.golemina<<" - "<<v.sirina<<" - "<<v.price()<<endl;
        return o;
    }
};
class MusicVideo : public AudioRecording, public VideoRecording{
    char datum[9];
public:
    MusicVideo(char *naslov="", char *avtor="", int traenje=0, int golemina=0, int type=0, short channels=0, int sirina=0, int komp=0, char *datum="")
    : MediaSegment(naslov, avtor, traenje, golemina){
        this->type=(format)type;
        this->channels=channels;
        this->komp=(kompresija)komp;
        this->sirina=sirina;
        strcpy(this->datum, datum);
    }
    float price()const{
        float cena=AudioRecording::price()+VideoRecording::price();
        if (strcmp(datum + 4, "2010") > 0)
            return 1.3*cena;
        return cena;
    }
    friend ostream &operator<<(ostream &out, const MusicVideo &mv) {
        return out << mv.naslov << " - " << mv.avtor<< " - " << mv.datum << " - " << mv.traenje << " - " << mv.price();
    }
};
float total_price(MediaSegment **ms, int n){
    float vkupno=0;
    for (int i=0; i<n; i++)
        vkupno+=ms[i]->price();
    return vkupno;
}
MusicVideo cheapest_music_video (MediaSegment **ms, int n){
    MusicVideo *najevtino=nullptr;
    for (int i=0; i<n; i++){
        MusicVideo *mv=dynamic_cast<MusicVideo*>(ms[i]);
        if (mv){
            if (najevtino==nullptr) najevtino= mv;
            else
                if (mv->price()<najevtino->price())
                    najevtino = mv;
            }
    }
    return *najevtino;
}

int main() {

  int test_case_num;
  cin>>test_case_num;


  // for MediaSegment
  char title[100];
  char author[1000];
  unsigned int size;
  unsigned int duration;


  // for AudioRecording
  //-------------------
  unsigned short channels;

  // AudioFormat:
  // 0 - mp3
  // 1 - wav
  // 2 - ogg
  // 3 - flac
  unsigned short format;


  // for VideoRecording
  //-------------------
  unsigned short width;

  // VideoCompression:
  // 0 - x264
  // 1 - Theora
  // 2 - AV1
  int compression;


  // for MusicVideo
  //-------------------
  char publication_date[9];


  if (test_case_num == 1){
    cout<<"Testing class AudioRecording and operator<<"<<std::endl;
    cin.get();
    cin.getline(title,100);
    cin.getline(author, 100);
    //cin.get();
    cin >> duration >> size;
    cin >> format >> channels;

    AudioRecording a(title, author, duration, size, format, channels);

    cout<<a;

  }

  else if (test_case_num == 2){
    cout<<"Testing class VideoRecording and operator<<"<<std::endl;
    cin.get();
    cin.getline(title,100);
    cin.getline(author, 100);
    //cin.get();
    cin >> duration >> size;
    cin >> width >> compression;

    VideoRecording v(title, author, duration, size, width, compression);

    cout<<v;

  }

  else if (test_case_num == 3){
    cout<<"Testing class MusicVideo and operator<<"<<std::endl;

    cin.get();
    cin.getline(title,100);
    cin.getline(author, 100);
    //cin.get();
    cin >> duration >> size;

    cin >> format >> channels;
    cin >> width >> compression;

    cin.get();
    cin.getline(publication_date, 9);
    MusicVideo mv(title, author, duration, size, format, channels, width, compression, publication_date);

    cout << mv;
  }

  else if (test_case_num == 4){
    cout<<"Testing function: total_price "<<std::endl;

    MediaSegment ** m;

    int num_media_segments;
    cin >> num_media_segments;

    // 1 - AudioRecording
    // 2 - VideoRecording
    // 3 - MusicVideo
    short media_type;

    m = new MediaSegment*[num_media_segments];

    for (int i=0; i<num_media_segments; i++) {

      cin >> media_type;

      cin.get();
      cin.getline(title,100);
      cin.getline(author, 100);
      //cin.get();
      cin >> duration >> size;

      switch(media_type) {
      case 1:
              cin >> format >> channels;
              m[i] = new AudioRecording(title, author, duration, size, format, channels);
          break;
      case 2:
              cin >> width >> compression;
              m[i] = new VideoRecording(title, author, duration, size, width, compression);
          break;
      case 3:
              cin >> format >> channels;
              cin >> width >> compression;
              cin.get();
              cin.getline(publication_date, 9);
              m[i] = new MusicVideo(title, author, duration, size, format, channels, width, compression, publication_date);
          break;
      }
    }

    //for (int i=0;i<num_media_segments; i++){
    //    cout << *m[i];
    //}

    cout<< "Total price is: " << total_price(m, num_media_segments);

    delete [] m;

  }
  else if (test_case_num == 5){
    cout<<"Testing function: cheapest_music_video "<<std::endl;

    MediaSegment ** m;

    int num_media_segments;
    cin >> num_media_segments;

    // 1 - AudioRecording
    // 2 - VideoRecording
    // 3 - MusicVideo
    short media_type;

    m = new MediaSegment*[num_media_segments];

    for (int i=0; i<num_media_segments; i++) {

      cin >> media_type;

      cin.get();
      cin.getline(title,100);
      cin.getline(author, 100);
      //cin.get();
      cin >> duration >> size;

      switch(media_type) {
      case 1:
              cin >> format >> channels;
              m[i] = new AudioRecording(title, author, duration, size, format, channels);
          break;
      case 2:
              cin >> width >> compression;
              m[i] = new VideoRecording(title, author, duration, size, width, compression);
          break;
      case 3:
              cin >> format >> channels;
              cin >> width >> compression;
              cin.get();
              cin.getline(publication_date, 9);
              m[i] = new MusicVideo(title, author, duration, size, format, channels, width, compression, publication_date);
          break;
      }
    }

    cout << cheapest_music_video(m, num_media_segments);

    delete [] m;
  }

  return 0;
}
