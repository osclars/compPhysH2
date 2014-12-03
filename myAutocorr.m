
clf
data = load('energy.data');

localEnergy=data(:,1);
meanEnergy=data(:,2);
%% Energy autocorr
%plot([0 1200],[0.135 0.135],'k--')
hold on
%plot([0 1200],[-0.135 -0.135],'k--')

tmp=autocorr(meanEnergy,1200,[],3);
plot(tmp,'color','blue')
str={'x=461','y=0.1'};

tmp2=autocorr(localEnergy,1200,[],3);

plot(tmp2,'color','red')
%axis([0,1200,-0.5,1.1]);
set(gca,'fontsize',16);
xlabel('Number of time steps','fontsize',16)
ylabel('Correlation','fontsize',16)
title('Temperature correlation functions','fontsize',16)
legend('Correlation limit', '','773K','973K')
grid on
hold off


