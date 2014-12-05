
clf
data = load('energy.data');

localEnergy=data(:,1);
%% Energy autocorr
plotMax=150;
plot([0 plotMax],[0.135 0.135],'k--')
hold on
plot([0 plotMax],[-0.135 -0.135],'k--')

str={'x=461','y=0.1'};

tmp2=autocorr(localEnergy,plotMax,[],3);

plot(tmp2,'color','red','LineWidth',2)
axis([0,plotMax,-0.5,1.1]);
set(gca,'fontsize',20);
xlabel('Number of time steps','fontsize',20)
ylabel('Correlation','fontsize',20)
title('Energy correlation function','fontsize',20)
legend('Correlation limit', '','Local energy')
grid on
hold off


