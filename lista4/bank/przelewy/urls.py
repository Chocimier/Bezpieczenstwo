from django.conf.urls import url

from . import views

urlpatterns = [
    url(r'^$', views.index, name='index'),
    url(r'^przelewy/', views.transfers, name='transfers'),
    url(r'^dane_przelewu/', views.transfer_form, name='transfer_form'),
    url(r'^wyslij_dane/', views.transfer_form_target, name='transfer_form_target'),
    url(r'^potwierdz_dane/(?P<unconfirmed_id>[0-9]+)/', views.make_transfer, name='make_transfer'),
    url(r'^przelej/', views.make_transfer_target, name='make_transfer_target'),
    url(r'^potwierdzenie_przelewu/(?P<id>[0-9]+)/', views.transfer_details, name='transfer_details'),
]
